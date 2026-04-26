---
title: "Interface Control Document"
type: document
doc-id: ICD
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# Interface Control Document (ICD)

> Formal contract between PX4 flight controller and external systems.
> Any change to this document requires agreement from both parties.

## 1. Interface Summary

| IF-ID | This System | External System | Owner (Ext) | Protocol | Status |
|-------|-------------|----------------|-------------|----------|--------|
| ICD-001 | PX4 FMU (Pixhawk v6X) | QGroundControl GCS | Dronecode / GCS Team | MAVLink 2.0 | Released |
| ICD-002 | PX4 FMU | DroneCAN ESC (e.g., Holybro Kotleta) | ESC Vendor | DroneCAN v0 | Released |
| ICD-003 | PX4 FMU | ROS 2 Companion (Jetson / RPi) | Integrator | MAVLink 2.0 / DDS-XRCE | Released |
| ICD-004 | PX4 FMU | u-blox M9N GPS | u-blox | UBX binary | Released |

## 2. Interface Detail: ICD-001 — GCS MAVLink Telemetry

### 2.1 Physical Layer

| Parameter | Value |
|-----------|-------|
| Connection | UART (TELEM1 port) or USB |
| Connector | JST-GH 6-pin (TELEM1) |
| Cable | 6-wire with CTS/RTS flow control |
| Baud Rate | 921600 baud (default), configurable via `SER_TEL1_BAUD` |
| Signaling | 3.3 V TTL (via SiK radio converts to RF) |

### 2.2 Data Exchange

| Direction | Message | Frequency | Size | Description |
|-----------|---------|-----------|------|-------------|
| PX4 → GCS | `HEARTBEAT` | 1 Hz | 9 B | System mode, status, type |
| PX4 → GCS | `ATTITUDE` | 10–30 Hz | 28 B | Roll/pitch/yaw (rad) |
| PX4 → GCS | `GLOBAL_POSITION_INT` | 5 Hz | 28 B | Lat/lon (deg×10⁷), alt (mm) |
| PX4 → GCS | `BATTERY_STATUS` | 1 Hz | 41 B | Voltage, current, remaining % |
| PX4 → GCS | `STATUSTEXT` | Event-driven | ≤55 B | Human-readable alerts |
| GCS → PX4 | `COMMAND_LONG` | On demand | 33 B | Arm, disarm, takeoff, land, mode change |
| GCS → PX4 | `MISSION_ITEM_INT` | Batch upload | 37 B | Mission waypoints |
| GCS → PX4 | `PARAM_SET` | On demand | 23 B | Parameter write |

### 2.3 Timing

| Parameter | Value | Notes |
|-----------|-------|-------|
| Response timeout | 500 ms | GCS retries `COMMAND_LONG` if no `COMMAND_ACK` |
| Max latency | < 200 ms | Radio link dependent |
| Heartbeat interval | 1 sec | Both PX4 and GCS send; link-loss if missing 5 s |
| MAVLink stream rates | Configurable | `MAV_0_RATE` param (default 0 = auto) |

### 2.4 Error Handling

| Scenario | Detection | PX4 Action | GCS Action |
|----------|-----------|-----------|------------|
| No heartbeat 5 s | `telemetry_status.heartbeat_timeout` | Trigger `COM_DL_LOSS_T` failsafe (RTL/Land) | Show “Link Lost” |
| CRC error | MAVLink CRC mismatch | Drop packet silently, increment `rx_errors` | Same |
| Unknown MSG ID | ID not in message set | Log + ignore | Same |
| Command denied | `MAV_RESULT_DENIED` | Send ACK with denial reason | Show error reason |

## 3. Interface Detail: ICD-002 — DroneCAN ESC Control

### 3.1 Physical Layer

| Parameter | Value |
|-----------|-------|
| Connection | CAN bus (FDCAN1) |
| Connector | JST-GH 4-pin |
| Cable | Twisted pair (CAN-H, CAN-L) + GND + 5V |
| Bit Rate | 1 Mbps (CAN 2.0B extended frame) |
| Termination | 120 Ω at each end of bus |

### 3.2 Data Exchange

| Direction | Data Type | Frequency | Description |
|-----------|----------|-----------|-------------|
| PX4 → ESC | `esc.RawCommand` (ID 1030) | 50–400 Hz | Motor throttle commands (−14880 to +14880) |
| ESC → PX4 | `esc.Status` (ID 1034) | 10 Hz | RPM, voltage, current, temperature |
| PX4 → ESC | `protocol.param.GetSet` (ID 11/12) | On demand | ESC parameter read/write |

## 4. Change Control

> Changes to this ICD require:
> 1. Written agreement from both interface parties
> 2. Entry in `CHANGELOG.md`
> 3. Updated version in frontmatter
> 4. For MAVLink: changes go through MAVLink common message set review process

## 5. References

| Ref | Document | Version |
|-----|----------|--------|
| [1] | MAVLink Protocol v2.0 Specification | 2017 |
| [2] | DroneCAN (UAVCAN v0) Specification | 2020 |
| [3] | DO-178C — Software Considerations in Airborne Systems (ICD guidance) | 2011 |
| [4] | UART/SPI/I2C Bus Standards | — |
| [5] | Protocol-Overview.md | 1.0 |
| [6] | Message-Format.md | 1.0 |

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
