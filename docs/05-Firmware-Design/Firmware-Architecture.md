---
title: "Firmware Architecture"
type: document
doc-id: SDD-ARCH
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# Firmware Architecture

> **SRS Traceability**: This document is the top-level SDD and satisfies design decomposition for:
> SRS-F-001 (attitude estimation), SRS-F-002 (position control), SRS-F-006 (RC loss RTL), SRS-F-011 (MAVLink), SRS-F-029 (mode switching), SRS-NF-001 (MCU resource constraints).
> See [Traceability-Matrix.md](../01-Product-Scope/Traceability-Matrix.md) for full mapping.

## 1. Overview

| Parameter | Value |
|-----------|-------|
| Architecture Style | Modular publish-subscribe (uORB), work-queue scheduled |
| RTOS | NuttX 12.x (POSIX-compliant, preemptive, tickless) |
| Language | C11 / C++17 |
| Compiler | arm-none-eabi-gcc 12.x |
| Build System | CMake 3.22+ with Kconfig for board configs |

## 2. Layer Diagram

```
┌──────────────────────────────────────────────────────────────┐
│  APP    │Commander│EKF2│Navigator│MC_Rate│MC_Pos│FW_Att│VTOL│
├──────────────────────────────────────────────────────────────┤
│  SVC    │MAVLink│Logger│Param│ControlAlloc│FlightModeManager │
├──────────────────────────────────────────────────────────────┤
│  uORB   │Publish│Subscribe│Advertise│Zero-copy shared mem   │
├──────────────────────────────────────────────────────────────┤
│  WQ     │WorkQueueManager│Scheduled callbacks│Priority-based │
├──────────────────────────────────────────────────────────────┤
│  DRV    │ICM42688P│BMI088│BMP388│IST8310│GPS│PWM│CAN│RC    │
├──────────────────────────────────────────────────────────────┤
│  BSP    │Board init│Clock│Pin config│SPI/I2C/UART instances  │
└──────────────────────────────────────────────────────────────┘
```

## 3. Task Model (Work Queues)

PX4 uses **work queues** instead of traditional per-module tasks. Each module registers a `Run()` callback on a named work queue.

| Work Queue | Rate | Priority | Modules |
|-----------|------|----------|---------|
| `wq:rate_ctrl` | 1–8 kHz | Highest (253) | `mc_rate_control`, `fw_rate_control` |
| `wq:INS0` | 1–8 kHz | 250 | `sensor_accel` driver, `sensor_gyro` driver |
| `wq:INS1` | 1–8 kHz | 250 | Secondary IMU driver instances |
| `wq:nav_and_controllers` | 50–250 Hz | 240 | `mc_pos_control`, `navigator`, `ekf2` |
| `wq:hp_default` | Variable | 230 | `commander`, `land_detector`, `control_allocator` |
| `wq:lp_default` | Variable | 205 | `logger`, `mavlink`, `battery_status` |
| `wq:I2C0` | Variable | 220 | I2C sensor drivers (IST8310 mag) |

## 4. Inter-Module Communication (uORB)

All module communication goes through uORB topics — **no function calls between modules**.

| Publisher | Topic | Subscriber | Data | Rate |
|-----------|-------|-----------|------|------|
| `sensor_accel` driver | `sensor_accel` | `ekf2` | Raw accelerometer XYZ | 1–8 kHz |
| `sensor_gyro` driver | `sensor_gyro` | `mc_rate_control` | Raw gyroscope XYZ | 1–8 kHz |
| `ekf2` | `vehicle_attitude` | `mc_rate_control` | Quaternion attitude | 250 Hz |
| `ekf2` | `vehicle_local_position` | `mc_pos_control` | NED position + velocity | 250 Hz |
| `mc_rate_control` | `vehicle_torque_setpoint` / `vehicle_thrust_setpoint` | `control_allocator` | Torque + thrust commands | 250 Hz |
| `control_allocator` | `actuator_motors` | `pwm_out` / `uavcan` | Per-motor output values | 250 Hz |
| `commander` | `vehicle_status` | All modules | Arming state, flight mode | 10 Hz |
| `navigator` | `position_setpoint_triplet` | `mc_pos_control` | Mission waypoints | On change |
| `gps` driver | `vehicle_gps_position` | `ekf2` | GNSS position + velocity | 5–25 Hz |
| `rc_input` | `input_rc` | `manual_control` | RC channel values | 50 Hz |
| `mavlink` | `telemetry_status` | `commander` | GCS link quality | 1 Hz |

## 5. Interrupt Map

| IRQ | Source | Priority | Handler | Latency Req |
|-----|--------|----------|---------|------------|
| EXTI (IMU1 DRDY) | ICM-42688P INT1 | High | `icm42688p::data_ready_isr()` | < 10 µs |
| EXTI (IMU2 DRDY) | BMI088 INT1 | High | `bmi088::data_ready_isr()` | < 10 µs |
| DMA (SPI1 RX) | SPI transfer complete | Medium | DMA ISR → work queue schedule | < 20 µs |
| USART2 (TELEM) | MAVLink byte received | Medium | NuttX serial driver | < 100 µs |
| USART3 (GPS) | GPS byte received | Medium | NuttX serial driver | < 100 µs |
| FDCAN1 | CAN frame received | Medium | NuttX CAN driver | < 50 µs |
| TIM1 (PWM) | PWM period complete | Low | Timer ISR | Non-critical |
| IWDG | Watchdog timeout | — | Hardware reset | — |

## 6. Module Dependency Graph

```
Sensors (ICM42688P, BMI088, BMP388, IST8310, GPS)
    │ uORB: sensor_accel, sensor_gyro, sensor_baro, sensor_mag, vehicle_gps_position
    ▼
EKF2 (state estimator)
    │ uORB: vehicle_attitude, vehicle_local_position, vehicle_global_position
    ▼
Commander (state machine)  ◀──── RC Input / MAVLink (mode switch)
    │ uORB: vehicle_status, vehicle_command
    ▼
Flight Mode Manager ──▶ Navigator (mission) / Manual Control
    │ uORB: position_setpoint_triplet
    ▼
Position Controller (mc_pos_control / fw_pos_control)
    │ uORB: vehicle_attitude_setpoint, vehicle_rates_setpoint
    ▼
Rate Controller (mc_rate_control / fw_rate_control)
    │ uORB: vehicle_torque_setpoint / vehicle_thrust_setpoint
    ▼
Control Allocator
    │ uORB: actuator_motors, actuator_servos
    ▼
Outputs (pwm_out / DShot / uavcan)
```

## 7. Key Design Decisions

| Decision | Rationale | ADR |
|----------|-----------|-----|
| uORB as sole IPC | Decoupled modules, zero-copy, allows SITL | [ADR-0001](../02-System-Architecture/ADR/ADR-Index.md) |
| NuttX over FreeRTOS/Zephyr | POSIX API, filesystem, network stack, proven in flight | [ADR-0002](../02-System-Architecture/ADR/ADR-Index.md) |
| Work queues over dedicated tasks | Efficient CPU use, less stack memory, priority-based scheduling | — |
| Dynamic control allocator | Supports any motor geometry without custom mixer files | [ADR-0007](../02-System-Architecture/ADR/ADR-Index.md) |
| Cascaded PID (attitude → rate) | Industry standard, tunable, separate rate/attitude loops | — |
| ModuleBase pattern | Unified module lifecycle: init, start, stop, status | — |

## 8. Cross-References

- Boot flow → [Boot-Sequence.md](Boot-Sequence.md)
- Memory layout → [Memory-Partition.md](Memory-Partition.md)
- System context → [02-System-Architecture/System-Context.md](../02-System-Architecture/System-Context.md)

## 9. References

| Ref | Document | Version |
|-----|----------|--------|
| [1] | DO-178C — Software Considerations in Airborne Systems | 2011 |
| [2] | IEEE 12207 — Systems and Software Life Cycle Processes | 2017 |
| [3] | PX4 Architectural Overview (docs.px4.io/main/en/concept/architecture.html) | v1.16 |
| [4] | NuttX RTOS Documentation | 12.x |
| [5] | uORB Messaging (docs.px4.io/main/en/middleware/uorb.html) | v1.16 |
| [6] | MISRA C:2012 — Guidelines for the use of the C language | 2012 |

---

## Revision History

| Version | Date | Changes | Author | Approved By |
|---------|------|---------|--------|-------------|
| 1.0 | 2024-12-01 | Initial release | PX4 Dev Team | Release Manager |

## Approvals

| Role | Name | Date | Signature |
|------|------|------|-----------|
| Author | — | — | — |
| Reviewer | — | — | — |
| Approver | — | — | — |
