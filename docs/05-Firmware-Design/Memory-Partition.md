---
title: "Memory Partition"
type: document
doc-id: FW-MEM
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# Memory Partition Table

> **SRS Traceability**: This document satisfies design decomposition for:
> SRS-NF-001 (MCU resource constraints: ≤ 384 KB RAM), SRS-NF-005 (persistent storage for parameters/logs).
> See [Traceability-Matrix.md](../01-Product-Scope/Traceability-Matrix.md) for full mapping.

> STM32H753 (Pixhawk FMU-v6X) flash and RAM partition management for PX4.

## 1. Flash Layout

```
┌──────────────────────┐ 0x08000000
│   PX4 Bootloader     │  32 KB  (bl_fmu-v6x)
├──────────────────────┤ 0x08008000
│                      │
│   PX4 Firmware       │ ~1920 KB
│   (NuttX + modules   │
│    + ROMFS)          │
│                      │
├──────────────────────┤ 0x081F8000
│   Parameters (BSON)  │  32 KB  (param save/load)
├──────────────────────┤ 0x081FC000
│   Board Config       │  16 KB  (factory cal, serial)
└──────────────────────┘ 0x081FFFFF  (2 MB total)
```

## 2. Flash Partition Table

| Partition | Start | End | Size | Erase Unit | Write Protected | Purpose |
|-----------|-------|-----|------|-----------|----------------|---------|
| Bootloader | `0x08000000` | `0x08007FFF` | 32 KB | 128 KB (sector) | Yes (OTP lock) | USB DFU upload, jump to app |
| Firmware | `0x08008000` | `0x081F7FFF` | ~1920 KB | 128 KB | Runtime (read-only) | PX4 application + NuttX + ROMFS |
| Parameters | `0x081F8000` | `0x081FBFFF` | 32 KB | 128 KB | No | BSON param persistence (`param save`) |
| Board Config | `0x081FC000` | `0x081FFFFF` | 16 KB | 128 KB | Factory only | Board serial#, sensor calibration |

> **Note**: STM32H753 flash sector size is 128 KB. PX4 does NOT use A/B slot OTA — firmware upload goes through bootloader via USB or MAVLink `SERIAL_CONTROL`.

## 3. RAM Layout

| Region | Start | Size | Usage |
|--------|-------|------|-------|
| ITCM | `0x00000000` | 64 KB | ISR vectors + time-critical code (zero-wait) |
| DTCM | `0x20000000` | 128 KB | Main stack (8 KB), ISR stack (2 KB), critical .bss |
| AXI SRAM | `0x24000000` | 512 KB | NuttX heap, uORB topics, module stacks, .data, .bss |
| SRAM1+2 | `0x30000000` | 128 KB | DMA buffers (SPI, UART, SDIO), CAN message RAM |
| SRAM4 | `0x38000000` | 64 KB | Backup SRAM (power domain D3), RTC backup |

### Typical RAM Budget

| Category | Size | Notes |
|----------|------|-------|
| NuttX kernel heap | ~80 KB | Dynamic alloc (from AXI SRAM) |
| Work queue stacks | ~60 KB | 7 work queues × 4–12 KB each |
| uORB topic buffers | ~40 KB | 60+ topics, multi-instance |
| DMA buffers | ~16 KB | SPI RX/TX, UART circular |
| Module statics | ~100 KB | EKF2 alone uses ~40 KB |
| Free | ~200 KB | Available headroom |

## 4. Parameter Storage (BSON)

PX4 uses **BSON** (Binary JSON) format for parameter persistence in flash.

| Key Example | Type | Size | Default | Description |
|-------------|------|------|---------|-------------|
| `SYS_AUTOSTART` | int32 | 4 B | 0 | Airframe ID (e.g., 4001 = generic quad) |
| `MC_ROLLRATE_P` | float | 4 B | 0.15 | Roll rate PID P gain |
| `EKF2_HGT_REF` | int32 | 4 B | 1 | Height reference (0=baro, 1=GPS, 2=range) |
| `MAV_SYS_ID` | int32 | 4 B | 1 | MAVLink system ID |
| `COM_ARM_EKF_AB` | float | 4 B | 0.005 | Accel bias arm threshold (m/s²) |
| `BAT_V_DIV` | float | 4 B | 18.1 | Battery voltage divider ratio |
| `SENS_BOARD_ROT` | int32 | 4 B | 0 | Board rotation enum |
| `CAL_GYRO0_XOFF` | float | 4 B | 0.0 | Gyro X offset (rad/s) |

> Total ~900 parameters × ~8 B avg = ~7 KB typical used out of 32 KB partition.

## 5. External Storage (SD Card)

| Path | Purpose | Format |
|------|---------|--------|
| `/fs/microsd/log/` | ULog flight logs | `.ulg` binary |
| `/fs/microsd/dataman` | Mission storage, geofence | Binary |
| `/fs/microsd/parameters_backup.bson` | Param backup | BSON |
| `/fs/microsd/etc/` | ROMFS overlay (custom startup) | Scripts |
| `/fs/microsd/fault_*.log` | Hardfault dumps | Text |

## 6. Cross-References

- HW memory map → [04-HW-SW-Interface/Memory-Map.md](../04-HW-SW-Interface/Memory-Map.md)
- Boot flow → [Boot-Sequence.md](Boot-Sequence.md)

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
