---
title: "Protocol Overview"
type: document
doc-id: COM-OVR
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# Protocol Overview

## 1. Protocol Stack

```
┌───────────────────────────────────────────────────────────┐
│  Application  │ MAVLink 2.0     │ DroneCAN (UAVCAN v0)  │
├───────────────┼─────────────────┼───────────────────────-┤
│  Transport    │ Serial stream   │ CAN Transport Layer   │
├───────────────┼─────────────────┼───────────────────────-┤
│  Data Link    │ UART framing    │ CAN 2.0B / FDCAN      │
├───────────────┼─────────────────┼───────────────────────-┤
│  Physical     │ UART 3.3V TTL   │ CAN-H / CAN-L diff    │
└───────────────┴─────────────────┴───────────────────────-┘
```

Additionally, **uORB** handles all intra-flight-controller communication (not on a physical bus).

## 2. Communication Interfaces

| Interface | Physical | Protocol | Direction | Peer System | Baud / Rate | Notes |
|-----------|---------|----------|-----------|-------------|-------------|-------|
| TELEM1 | UART (USART2) | MAVLink 2.0 | Bidir | GCS (QGroundControl) | 921600 baud | Primary telemetry |
| TELEM2 | UART (UART7) | MAVLink 2.0 | Bidir | Companion computer (ROS 2) | 921600 baud | Secondary / onboard |
| GPS | UART (USART3) | UBX binary | Bidir | u-blox M9N GNSS | 115200 baud | Position/velocity |
| RC Input | UART (via IO) | SBUS / CRSF | Downlink | RC Receiver | 100 kbaud (SBUS) | Via IO co-processor |
| CAN 1 | FDCAN1 | DroneCAN (UAVCAN v0) | Bidir | ESC, sensors, GPS | 1 Mbps | Redundant bus |
| CAN 2 | FDCAN2 | DroneCAN | Bidir | Secondary peripherals | 1 Mbps | Redundant bus |
| USB | USB Full-Speed | MAVLink 2.0 / NSH | Bidir | Dev PC | 12 Mbps | Debug console + upload |
| uORB | Shared memory | Pub/Sub (zero-copy) | Bidir | Internal modules | In-process | Not a physical bus |

## 3. Protocol Selection Rationale

| Interface | Chosen Protocol | Alternatives Considered | Rationale |
|-----------|----------------|------------------------|-----------|
| GCS Link | MAVLink 2.0 | ROS 2 DDS, custom | Industry standard for UAVs; signing support; 280+ message types; compatible with QGC/Mission Planner |
| CAN Peripherals | DroneCAN (UAVCAN v0) | Cyphal (UAVCAN v1), PWM+analog | Node discovery, firmware update over bus, standardized ESC/GPS/mag messages |
| GPS | UBX binary | NMEA, RTCM | Higher precision (RTK capable), configurable rate, less parsing overhead than NMEA |
| RC | SBUS / CRSF | PPM, iBUS | Low latency, single-wire, 16+ channels |
| Internal IPC | uORB | ROS 2 DDS, shared vars | Zero-copy, < 1 µs publish latency, proven in flight-critical path |

## 4. Error Handling & Retries

| Interface | Error Detection | Retry Strategy | Max Retries | Timeout |
|-----------|----------------|---------------|-------------|---------|
| MAVLink | CRC-16 (X.25), sequence number | Re-request via `COMMAND_LONG` ACK | 3 | 500 ms |
| DroneCAN | CAN CRC + transport CRC | CAN automatic retransmit | Hardware | Bus arbitration |
| UBX GPS | Fletcher checksum (CK_A/CK_B) | Reconfigure on 3 consecutive fails | 3 | 1500 ms |
| SBUS RC | Frame checksum | Input timeout → RC_LOST flag | — | 500 ms |

## 5. Security

| Interface | Encryption | Authentication | Key Management |
|-----------|-----------|---------------|---------------|
| MAVLink 2.0 | None (plaintext) | Message signing (SHA-256, optional) | Shared secret key via QGC |
| DroneCAN | None | Node ID allocation | Centralized (PX4 allocator) |
| USB | None | Physical access only | — |

> **Note**: PX4 v1.16 does not enforce MAVLink signing by default. Enable `MAV_HASH_CHK_EN` for signed channels.

## 6. Cross-References

- Message details → [Message-Format.md](Message-Format.md)
- External contracts → [Interface-Control-Document.md](Interface-Control-Document.md)
- HW interface → [04-HW-SW-Interface/](../04-HW-SW-Interface/README.md)

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
