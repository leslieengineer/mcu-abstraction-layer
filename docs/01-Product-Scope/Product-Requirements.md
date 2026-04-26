---
title: "Product Requirements Document"
type: document
doc-id: PRD
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# Product Requirements Document (PRD)

## 1. Product Vision

PX4 Autopilot aims to be the world's most widely used open-source flight controller software, enabling safe, reliable autonomous flight for drones and unmanned vehicles across all vehicle types (multicopter, fixed-wing, VTOL, rover, submarine). It provides a complete sensor-to-actuator pipeline, from IMU data acquisition through sensor fusion (EKF2) to motor output, with communication to ground stations via MAVLink.

## 2. Target Users / Customers

| User Type | Description | Primary Need |
|-----------|-------------|-------------|
| Drone manufacturers | Companies building commercial drones | Reliable, certifiable flight stack |
| Researchers | Universities and labs studying UAV technology | Extensible, well-documented codebase |
| Hobbyists | DIY drone builders | Easy setup, community support |
| Defense/enterprise | Government and large organizations | Customizable, auditable, safety-critical |
| Developers | Software engineers contributing modules | Clean architecture, good APIs |

## 3. Functional Requirements

| ID | Category | Requirement | Priority | Rationale |
|----|----------|------------|----------|-----------|
| PRD-F-001 | Flight Control | Stabilized attitude control for MC, FW, VTOL | Must | Core autopilot function |
| PRD-F-002 | Flight Control | Position hold (GPS-based and optical flow) | Must | Hover stability |
| PRD-F-003 | Navigation | Autonomous waypoint mission execution | Must | Core mission capability |
| PRD-F-004 | Navigation | Return-To-Launch (RTL) failsafe | Must | Safety requirement |
| PRD-F-005 | Navigation | Geofence (inclusion and exclusion zones) | Must | Safety requirement |
| PRD-F-006 | Estimation | Multi-sensor fusion (IMU, GPS, baro, mag, optical flow) | Must | Accurate state estimation |
| PRD-F-007 | Estimation | Multi-EKF instance voting for redundancy | Should | Reliability improvement |
| PRD-F-008 | Communication | MAVLink 2.0 bidirectional with GCS | Must | Ground station interop |
| PRD-F-009 | Communication | MAVLink message signing for security | Should | Anti-spoofing |
| PRD-F-010 | Communication | DroneCAN peripheral support | Must | CAN bus sensors/actuators |
| PRD-F-011 | Actuator | PWM / DShot motor output | Must | Motor control |
| PRD-F-012 | Actuator | Dynamic control allocation (any mixer geometry) | Must | Flexible vehicle configs |
| PRD-F-013 | Safety | Commander arming/disarming state machine | Must | Safety gate |
| PRD-F-014 | Safety | Failsafe cascade (RC loss → data link loss → land) | Must | Fail-safe behavior |
| PRD-F-015 | Safety | Pre-flight health checks (sensor, GPS, battery) | Must | Safety verification |
| PRD-F-016 | Logging | ULog on-board flight logging | Must | Post-flight analysis |
| PRD-F-017 | Parameters | Runtime parameter system (3000+ params) | Must | Configuration flexibility |
| PRD-F-018 | OTA | Firmware update via USB and MAVLink | Must | Field update capability |
| PRD-F-019 | Simulation | SITL (Software-In-The-Loop) simulation | Must | Development and testing |
| PRD-F-020 | Simulation | HITL (Hardware-In-The-Loop) simulation | Should | Hardware validation |
| PRD-F-021 | Integration | ROS2 bridge via XRCE-DDS | Should | Robotics ecosystem |
| PRD-F-022 | Flight Modes | Manual, Altitude, Position, Mission, RTL, Land, Acro | Must | Operator flexibility |
| PRD-F-023 | Landing | Automatic landing detection (accelerometer + range) | Must | Safe auto-land |
| PRD-F-024 | VTOL | Transition between MC and FW modes | Must | VTOL vehicle support |
| PRD-F-025 | RC | Multi-protocol RC input (SBUS, CRSF, DSM, PPM) | Must | Radio compatibility |

## 4. Non-Functional Requirements

| ID | Category | Requirement | Metric |
|----|----------|------------|--------|
| PRD-NF-001 | Performance | Attitude control loop ≤ 250 µs (4 kHz rate) | Loop time measured via `perf` counters |
| PRD-NF-002 | Performance | EKF2 update ≤ 1 ms at 250 Hz | CPU usage < 15% |
| PRD-NF-003 | Reliability | Mean Time Between Failure > 1000 flight-hours | Field data from community |
| PRD-NF-004 | Reliability | Watchdog recovery from firmware crash < 500 ms | Measured from hardfault to re-arm |
| PRD-NF-005 | Power | Idle power consumption < 500 mW (FMU only) | Measured at VBUS |
| PRD-NF-006 | Memory | Firmware binary ≤ 2 MB Flash | Build output size |
| PRD-NF-007 | Memory | Total RAM usage ≤ 384 KB on STM32H7 | `free` command on NSH |
| PRD-NF-008 | Latency | RC input to motor output ≤ 10 ms | End-to-end latency |
| PRD-NF-009 | Boot Time | Power-on to ready ≤ 5 seconds | Measured via logger |
| PRD-NF-010 | Portability | Support ≥ 80 board configurations | Board count in build system |

## 5. Regulatory & Compliance

| Standard           | Scope                                 | Notes                                              |
| ------------------ | ------------------------------------- | -------------------------------------------------- |
| MAVLink 2.0        | Communication protocol                | Full compliance, message signing optional          |
| DroneCAN v1/Cyphal | CAN bus peripherals                   | Standard node implementation                       |
| DO-178C            | Software development (reference only) | Not certified, but architecture follows principles |
| EASA SC-Light-UAS  | EU drone regulations                  | Category-specific compliance                       |
| FAA Part 107       | US drone regulations                  | Operator responsibility                            |

## 6. Interface Requirements

> High-level interfaces. Detailed in [06-Communication-Protocol/](../06-Communication-Protocol/README.md)

| Interface | Type | External System | Protocol |
|-----------|------|----------------|----------|
| GCS Telemetry | Logical (serial/UDP) | QGroundControl | MAVLink 2.0 |
| RC Receiver | Physical (serial) | RC Transmitter | SBUS/CRSF/DSM |
| CAN Peripherals | Physical (CAN bus) | ESC, GPS, Airspeed | DroneCAN/Cyphal |
| Onboard Computer | Logical (serial/Ethernet) | ROS2 Companion | XRCE-DDS/MAVLink |
| USB | Physical (USB) | PC (firmware upload/NSH) | Serial CDC |
| SD Card | Physical (SDIO/SPI) | MicroSD | FAT32 (ULog storage) |

## 7. Environmental & Physical Constraints

| Parameter | Specification |
|-----------|--------------|
| Operating Temperature | −40°C to +85°C (Pixhawk standard) |
| Storage Temperature | −55°C to +125°C |
| Humidity | 0–95% non-condensing |
| Vibration | Up to 5g RMS (with proper mounting) |
| Altitude | 0–10,000 m ASL (barometer range dependent) |
| Input Voltage | 4.1 V – 5.7 V (Pixhawk power standard) |

## 8. Acceptance Criteria

1. All SITL regression tests pass on MC, FW, VTOL vehicle types
2. Stable hover ≥ 30 min on Pixhawk v6X with no EKF divergence
3. RTL failsafe triggers within 5 seconds of RC loss
4. QGroundControl mission upload/download works without error
5. ULog contains all required topics for post-flight analysis

## 9. References

| Ref | Document | Version |
|-----|----------|--------|
| [1] | DO-178C — Software Considerations in Airborne Systems | 2011 |
| [2] | IEEE 830 — Recommended Practice for SRS | 1998 |
| [3] | MAVLink Protocol Specification v2.0 | 2017 |
| [4] | PX4 Developer Guide — https://docs.px4.io | v1.16 |
| [5] | STM32H753 Reference Manual (RM0433) | Rev 8 |
| [6] | Pixhawk Autopilot Bus Standard | FMUv6X |

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
