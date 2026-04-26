---
title: "Message Format Specification"
type: document
doc-id: COM-MSG
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# Message Format Specification

## 1. MAVLink 2.0 Frame Structure

```
┌───────────┬───────────┬─────┬─────┬─────┬────────┬──────────────┬───────┬───────────┐
│ STX (0xFD) │ Payload Len │ IFG │ CMP │ SEQ │ SYS ID │ COMP ID      │ MSG ID│ Payload    │
│ 1 B        │ 1 B         │ 1 B │ 1 B │ 1 B │ 1 B    │ 1 B          │ 3 B   │ 0–255 B    │
├───────────┴───────────┴─────┴─────┴─────┴────────┴──────────────┴───────┴───────────┤
│ CRC-16 X.25 (2 B)                                    │ Signature (optional, 13 B)   │
└─────────────────────────────────────────────────────┴─────────────────────────────┘
```

## 2. MAVLink Field Definitions

| Field | Offset | Size | Type | Description | Values |
|-------|--------|------|------|-------------|--------|
| STX | 0 | 1 B | uint8 | Start marker (v2) | `0xFD` |
| Payload Len | 1 | 1 B | uint8 | Payload byte count | 0–255 |
| Incompat Flags | 2 | 1 B | uint8 | Incompatibility flags | Bit 0 = signed |
| Compat Flags | 3 | 1 B | uint8 | Compatibility flags | Reserved |
| Sequence | 4 | 1 B | uint8 | Packet sequence counter | 0–255, wraps |
| System ID | 5 | 1 B | uint8 | Sending system ID | 1–255 |
| Component ID | 6 | 1 B | uint8 | Sending component | 1 = autopilot |
| Message ID | 7 | 3 B | uint24_le | Message type | 0–16777215 |
| Payload | 10 | 0–255 B | bytes | Message data | Message-specific |
| CRC | 10+N | 2 B | uint16 | CRC-16/X.25 with CRC_EXTRA seed | Calculated |
| Signature | 12+N | 13 B | bytes | Optional SHA-256 signature | If INCOMPAT_FLAGS bit 0 set |

## 3. Key MAVLink Messages (PX4 v1.16)

| MSG ID | Name | Direction | Frequency | Description |
|--------|------|-----------|-----------|-------------|
| 0 | `HEARTBEAT` | PX4 → GCS | 1 Hz | System alive, mode, status |
| 1 | `SYS_STATUS` | PX4 → GCS | 1 Hz | Battery, sensor health |
| 24 | `GPS_RAW_INT` | PX4 → GCS | 5 Hz | Raw GPS position |
| 30 | `ATTITUDE` | PX4 → GCS | 10–30 Hz | Roll, pitch, yaw (rad) |
| 32 | `LOCAL_POSITION_NED` | PX4 → GCS | 10 Hz | NED position + velocity |
| 33 | `GLOBAL_POSITION_INT` | PX4 → GCS | 5 Hz | Lat/lon/alt (deg×10⁷) |
| 76 | `COMMAND_LONG` | GCS → PX4 | On demand | Arm, disarm, takeoff, land, mode |
| 77 | `COMMAND_ACK` | PX4 → GCS | On demand | Command result acknowledgement |
| 87 | `POSITION_TARGET_GLOBAL_INT` | GCS → PX4 | On demand | Guided waypoint |
| 147 | `BATTERY_STATUS` | PX4 → GCS | 1 Hz | Cell voltages, remaining % |
| 242 | `HOME_POSITION` | PX4 → GCS | On change | Home lat/lon/alt |
| 253 | `STATUSTEXT` | PX4 → GCS | Event | Human-readable status messages |

## 4. DroneCAN Message Format

```
CAN 2.0B Extended Frame (29-bit ID):
┌──────────────┬───────────┬──────────┬────────────┐
│ Priority (5b) │ DTID (16b) │ Svc/Msg   │ Source (7b)  │
└──────────────┴───────────┴──────────┴────────────┘
Payload: 0–8 bytes per frame (multi-frame via toggle + CRC)
```

### Key DroneCAN Data Types

| Data Type ID | Name | Direction | Description |
|-------------|------|-----------|-------------|
| 1030 | `uavcan.equipment.esc.RawCommand` | PX4 → ESC | Throttle commands (−14880–+14880) |
| 1034 | `uavcan.equipment.esc.Status` | ESC → PX4 | RPM, voltage, current, temp |
| 1060 | `uavcan.equipment.gnss.Fix2` | GPS → PX4 | GNSS position fix |
| 1028 | `uavcan.equipment.actuator.ArrayCommand` | PX4 → Servo | Servo position commands |
| 341 | `uavcan.protocol.NodeStatus` | All | Node health heartbeat (1 Hz) |
| 1 | `uavcan.protocol.GetNodeInfo` | Query | Node name, SW/HW version |

## 5. uORB Internal Message Format

uORB messages are C structs defined in `msg/*.msg` files, auto-generated to C headers.

```c
/* Example: sensor_accel_s */
struct sensor_accel_s {
    uint64_t timestamp;          // µs since boot (hrt_absolute_time)
    uint64_t timestamp_sample;   // actual sample time
    uint32_t device_id;          // unique sensor identifier
    float x;                     // m/s²
    float y;
    float z;
    float temperature;           // °C
    uint32_t error_count;
    uint8_t clip_counter[3];     // clipping events per axis
};
```

## 6. Error Codes

### MAVLink

| Code | Name | Description | Recovery |
|------|------|-------------|----------|
| 0 | `MAV_RESULT_ACCEPTED` | Command accepted | — |
| 1 | `MAV_RESULT_TEMPORARILY_REJECTED` | Retry later | Retry in 1 s |
| 2 | `MAV_RESULT_DENIED` | Permanently denied | Check params |
| 3 | `MAV_RESULT_UNSUPPORTED` | Unknown command | — |
| 4 | `MAV_RESULT_FAILED` | Execution failed | Check logs |
| 5 | `MAV_RESULT_IN_PROGRESS` | Long-running operation | Poll for ACK |

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
