---
title: "System Context & Container"
type: document
doc-id: SAD
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# System Context & Container

## 1. System Context Diagram

> Shows PX4 as a black box and all external actors/systems.

```
┌────────────────┐     ┌──────────────────────────┐     ┌────────────────┐
│  RC Transmitter │────▶│                          │────▶│  ESC / Motors  │
│  (SBUS/CRSF)   │     │                          │     │  (PWM/DShot)   │
└────────────────┘     │                          │     └────────────────┘
                       │     PX4 Autopilot        │
┌────────────────┐     │     (NuttX RTOS)         │     ┌────────────────┐
│  QGroundControl │◀──▶│                          │◀──▶│  CAN Peripherals│
│  (MAVLink 2.0)  │     │  STM32H7 / Pixhawk      │     │  (DroneCAN)    │
└────────────────┘     │                          │     └────────────────┘
                       │                          │
┌────────────────┐     │                          │     ┌────────────────┐
│  Onboard Sensors│────▶│                          │────▶│  SD Card       │
│  IMU/Baro/Mag  │     │                          │     │  (ULog/Params) │
│  GPS           │     └──────────────────────────┘     └────────────────┘
└────────────────┘              │         ▲
                                ▼         │
                       ┌──────────────────────────┐
                       │  ROS2 Companion Computer  │
                       │  (XRCE-DDS / MAVLink)     │
                       └──────────────────────────┘
```

### External Actors

| Actor | Type | Interface | Protocol | Description |
|-------|------|-----------|----------|-------------|
| RC Transmitter | Human input | UART (serial) | SBUS / CRSF / DSM / PPM | Pilot manual control |
| QGroundControl | System | UART / UDP / TCP | MAVLink 2.0 | Ground control station — mission, params, telemetry |
| Onboard Sensors | Hardware | SPI / I2C | Native register | IMU (accel+gyro), barometer, magnetometer, GPS |
| ESC / Motors | Actuator | PWM / DShot / CAN | PWM / DShot / DroneCAN | Motor speed control + RPM feedback |
| CAN Peripherals | System | CAN bus | DroneCAN v1 / Cyphal | External GPS, airspeed, mag, ESC, rangefinder |
| SD Card | Storage | SDIO / SPI | FAT32 filesystem | ULog flight logs, parameter files, ROMFS |
| Companion Computer | System | Serial / Ethernet | XRCE-DDS / MAVLink | ROS2 integration, offboard control, CV |

## 2. Container Diagram

> Shows the major technology/runtime containers within PX4.

### Containers

| Container | Technology | Responsibility | Interfaces |
|-----------|-----------|---------------|------------|
| FMU (Main Processor) | STM32H753 (Cortex-M7, 480 MHz) | All flight control, estimation, navigation, communication | SPI, I2C, UART, CAN, USB, SDIO |
| IO Co-processor | STM32F100 (Cortex-M3) | RC input parsing, PWM failsafe output, safety button | UART (to FMU), PWM out, SBUS in |
| Sensor Suite | ICM42688P, BMI088, BMP388, IST8310 | Raw sensor data acquisition | SPI / I2C to FMU |
| Power Module | Pixhawk power brick | Battery V/I measurement, regulated 5V | ADC to FMU |
| GPS Module | u-blox M9N / M10 | GNSS position + velocity | UART / I2C / CAN |

## 3. Key Quality Attributes

| Attribute | Requirement | Design Decision |
|-----------|------------|----------------|
| Reliability | MTBF > 1000 hr, no single-point failure on critical sensors | Dual IMU, dual baro, multi-EKF voting |
| Performance | Attitude loop ≤ 250 µs, EKF ≤ 1 ms | Work queue scheduling, zero-copy uORB |
| Security | MAVLink signing, no remote code exec | Message signing, no dynamic loading |
| Power Consumption | FMU < 500 mW idle | ARM WFI sleep, peripheral gating |
| Maintainability | 500+ contributors, 13+ years of development | Modular architecture, clear module API |

## 4. Technology Stack

| Layer | Technology | Version | Notes |
|-------|-----------|---------|-------|
| MCU | STM32H753 / STM32F765 | — | ARM Cortex-M7, FPU, 480/216 MHz |
| RTOS | NuttX | 12.x | POSIX-compliant, tickless, priority preemptive |
| Compiler | arm-none-eabi-gcc | 12.x | C11 / C++17 |
| Build System | CMake + Kconfig | 3.22+ | Per-board `.px4board` config files |
| Communication | MAVLink 2.0 | 2.0 | Auto-generated from XML definitions |
| Messaging | uORB | — | Zero-copy publish-subscribe on NuttX |
| Simulation | Gazebo / jMAVSim | Gazebo 11+ | SITL via identical PX4 code on POSIX |

## 5. Cross-References

- Detailed firmware architecture → [05-Firmware-Design/Firmware-Architecture.md](../05-Firmware-Design/Firmware-Architecture.md)
- HW/SW interfaces → [04-HW-SW-Interface/](../04-HW-SW-Interface/README.md)
- Protocol details → [06-Communication-Protocol/](../06-Communication-Protocol/README.md)

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
