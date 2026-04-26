---
title: "Requirements Baseline"
type: document
doc-id: SRS
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# Requirements Baseline (SRS)

> Approved Software Requirements Specification baseline.
> All requirements here are **frozen** and under change control.

## 1. Baseline Info

| Field | Value |
|-------|-------|
| Baseline Version | 1.0 |
| Baseline Date | 2024-12-15 |
| Approved By | PX4 Release Manager |
| Source PRD Version | PRD v1.0 |

## 2. Requirements Summary

| Category | Count | Must | Should | Could |
|----------|-------|------|--------|-------|
| Functional | 35 | 28 | 5 | 2 |
| Non-Functional | 10 | 7 | 3 | 0 |
| Interface | 6 | 5 | 1 | 0 |
| **Total** | **51** | **40** | **9** | **2** |

## 3. Functional Requirements

| Req-ID | Description | Priority | Acceptance Criteria | Trace-To |
|--------|-------------|----------|-------------------|----------|
| SRS-F-001 | Attitude stabilization for all vehicle types (MC, FW, VTOL) using cascaded PID at ≥ 250 Hz | Must | Stable hover ≥ 30 min, no oscillation | PRD-F-001 |
| SRS-F-002 | Rate controller processes gyro data at sensor rate (up to 8 kHz) via work queue | Must | Loop jitter < 5% | PRD-F-001 |
| SRS-F-003 | Position hold using GPS with accuracy ≤ 1 m CEP in open sky | Must | Drift < 0.5 m over 60 sec hover | PRD-F-002 |
| SRS-F-004 | Optical flow position hold when GPS unavailable | Should | Stable hover over textured surface | PRD-F-002 |
| SRS-F-005 | Waypoint navigation with ≤ 2 m acceptance radius | Must | Complete 10-waypoint mission autonomously | PRD-F-003 |
| SRS-F-006 | Return-To-Launch activates on RC loss after configurable timeout (default 5 sec) | Must | Vehicle returns to launch within 30 sec | PRD-F-004 |
| SRS-F-007 | Geofence enforces inclusion/exclusion polygons with configurable action (RTL/Land/Hold) | Must | Vehicle does not cross fence boundary | PRD-F-005 |
| SRS-F-008 | EKF2 fuses IMU + GPS + baro + mag with configurable sensor masks | Must | Position RMS error < 2 m (GPS available) | PRD-F-006 |
| SRS-F-009 | EKF2 uses 24-state extended Kalman filter with quaternion attitude | Must | Innovation test ratio < 1.0 in normal flight | PRD-F-006 |
| SRS-F-010 | Multi-EKF instance support (up to 9 instances) with voting | Should | Switch to healthy instance within 100 ms | PRD-F-007 |
| SRS-F-011 | MAVLink 2.0 bidirectional communication on up to 4 serial ports | Must | Message loss < 0.1% on dedicated link | PRD-F-008 |
| SRS-F-012 | MAVLink stream rates configurable per port | Must | Configurable 1–100 Hz per stream | PRD-F-008 |
| SRS-F-013 | MAVLink message signing (SHA-256 HMAC) | Should | Reject unsigned messages when enabled | PRD-F-009 |
| SRS-F-014 | DroneCAN ESC control with RPM feedback | Must | ESC responds within 2 ms | PRD-F-010 |
| SRS-F-015 | DroneCAN sensor (GPS, baro, mag, airspeed) integration | Must | Data available via uORB topic | PRD-F-010 |
| SRS-F-016 | PWM output 50–400 Hz with configurable range | Must | PWM jitter < 1 µs | PRD-F-011 |
| SRS-F-017 | DShot150/300/600/1200 digital motor protocol | Must | Bidirectional RPM telemetry | PRD-F-011 |
| SRS-F-018 | Dynamic control allocator (replaces static mixers) with any motor geometry | Must | Supports hex, octo, tilt-rotor | PRD-F-012 |
| SRS-F-019 | Commander module manages arming state with pre-flight checks | Must | Cannot arm with failed checks | PRD-F-013 |
| SRS-F-020 | Failsafe cascade: RC loss → Hold → RTL → Land → Disarm | Must | Each stage triggers after timeout | PRD-F-014 |
| SRS-F-021 | Battery failsafe with 3 levels (warning, critical, emergency) | Must | Emergency land triggers at configurable voltage | PRD-F-014 |
| SRS-F-022 | Pre-flight checks: sensor health, GPS lock, battery level, RC | Must | Block arming on failure | PRD-F-015 |
| SRS-F-023 | ULog recording to SD card with configurable topics | Must | Continuous logging, no data gaps | PRD-F-016 |
| SRS-F-024 | Parameter system with 3000+ parameters, persistent storage (BSON format) | Must | Save/load within 100 ms | PRD-F-017 |
| SRS-F-025 | Firmware update via USB serial (bootloader) | Must | Flash in < 60 sec | PRD-F-018 |
| SRS-F-026 | SITL simulation via identical code on POSIX host | Must | Same output as hardware | PRD-F-019 |
| SRS-F-027 | HITL simulation via MAVLink to simulator | Should | < 5 ms round-trip latency | PRD-F-020 |
| SRS-F-028 | ROS2 topics via micro-XRCE-DDS agent | Should | < 10 ms topic latency | PRD-F-021 |
| SRS-F-029 | Flight mode switching: Manual, Altitude, Position, Mission, RTL, Land, Acro, Stabilized, Offboard | Must | Mode switch < 50 ms | PRD-F-022 |
| SRS-F-030 | Land detector using accelerometer + range sensor + thrust level | Must | Detection within 2 sec of touchdown | PRD-F-023 |
| SRS-F-031 | VTOL transition (MC ↔ FW) with configurable transition speed and altitude | Must | Smooth transition < 15 sec | PRD-F-024 |
| SRS-F-032 | Multi-protocol RC input: SBUS, CRSF, DSM, PPM via serial parser | Must | Channel decode < 20 ms latency | PRD-F-025 |
| SRS-F-033 | Work queue manager for real-time scheduling of module Run() callbacks | Must | Priority-correct execution | — |
| SRS-F-034 | uORB publish-subscribe for all inter-module communication | Must | Zero-copy, lock-free | — |
| SRS-F-035 | NSH console access via USB and MAVLink shell for diagnostics | Must | Interactive debug | — |

## 4. Non-Functional Requirements

| Req-ID | Category | Description | Metric | Trace-To |
|--------|----------|-------------|--------|----------|
| SRS-NF-001 | Performance | Rate control loop executes in ≤ 250 µs | perf counter | PRD-NF-001 |
| SRS-NF-002 | Performance | EKF2 update completes in ≤ 1 ms at 250 Hz | perf counter | PRD-NF-002 |
| SRS-NF-003 | Reliability | Watchdog reset recovery < 500 ms | Boot log | PRD-NF-004 |
| SRS-NF-004 | Memory | FW binary ≤ 2 MB Flash | build output `.bin` size | PRD-NF-006 |
| SRS-NF-005 | Memory | RAM usage ≤ 384 KB (STM32H7) | `free` command | PRD-NF-007 |
| SRS-NF-006 | Latency | RC-to-motor output ≤ 10 ms | Scope measurement | PRD-NF-008 |
| SRS-NF-007 | Boot | Power-on to scheduler ready ≤ 5 sec | Boot timestamp | PRD-NF-009 |
| SRS-NF-008 | Portability | Build for ≥ 80 board configs from same codebase | Board directory count | PRD-NF-010 |
| SRS-NF-009 | Power | FMU idle power < 500 mW | Current measurement | PRD-NF-005 |
| SRS-NF-010 | Reliability | MTBF > 1000 flight-hours | Community field data | PRD-NF-003 |

## 5. Interface Requirements

| Req-ID | Interface | Description | Protocol | Trace-To |
|--------|-----------|-------------|----------|----------|
| SRS-IF-001 | GCS Telemetry | Bidirectional MAVLink 2.0 on UART/UDP | MAVLink 2.0 | PRD-F-008 |
| SRS-IF-002 | RC Input | Multi-protocol serial RC receiver | SBUS/CRSF/DSM/PPM | PRD-F-025 |
| SRS-IF-003 | CAN Bus | DroneCAN peripheral communication | DroneCAN v1 / Cyphal | PRD-F-010 |
| SRS-IF-004 | Companion Computer | ROS2 bridge or MAVLink companion | XRCE-DDS / MAVLink | PRD-F-021 |
| SRS-IF-005 | USB | Firmware upload and NSH console | Serial CDC ACM | PRD-F-018 |
| SRS-IF-006 | SD Card | Flight log storage and parameter backup | FAT32 filesystem | PRD-F-016 |

## 6. Change History

| Version | Date | Changes | Approved By |
|---------|------|---------|-------------|
| 0.1 | 2024-11-01 | Initial draft from PRD v0.9 | — |
| 1.0 | 2024-12-15 | Baseline frozen for v1.16.1 release | PX4 Release Manager |

## Approvals

| Role | Name | Date | Signature |
|------|------|------|-----------|
| Author | — | — | — |
| Reviewer | — | — | — |
| Approver | — | — | — |
