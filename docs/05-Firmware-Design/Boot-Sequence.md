---
title: "Boot Sequence"
type: document
doc-id: FW-BOOT
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# Boot Sequence

> Power-on → application-ready flow for PX4 on Pixhawk FMU-v6X (STM32H753).

## 1. Boot Flow Diagram

```
[Power On / Reset]
    │
    ▼
[STM32H7 ROM]             ← Silicon boot, selects boot source (BOOT0 pin)
    │
    ▼
[PX4 Bootloader]          ← bl_fmu-v6x @ 0x08000000, 32 KB
    │
    ├── USB connected + boot delay?
    │   ├── Yes ──▶ [DFU/MAVLink firmware upload mode]
    │   └── No
    │
    ├── Valid app image? (check magic + CRC)
    │   ├── No ──▶ [Stay in bootloader, blink LED]
    │   └── Yes
    │
    ▼
[Jump to App @ 0x08008000]
    │
    ▼
[NuttX Kernel Init]       ← up_initialize(), clock 480 MHz, MPU, caches
    │
    ▼
[Board BSP Init]          ← stm32_boardinitialize(): GPIO, SPI, I2C, UART, DMA
    │
    ▼
[NuttX OS Start]          ← nx_start(): scheduler, work queues, idle task
    │
    ▼
[ROMFS Mount]             ← Mount /etc (startup scripts) from linked ROMFS image
    │
    ▼
[rcS Script Execution]    ← /etc/init.d/rcS → rc.autostart → board_defaults
    │
    ├── param load          ← Load BSON params from Flash/SD
    ├── sensor drivers start ← icm42688p, bmi088, bmp388, ist8310
    ├── estimator start      ← ekf2 module
    ├── controllers start    ← mc_rate_control, mc_pos_control, etc.
    ├── mavlink start        ← TELEM1, TELEM2 instances
    ├── logger start         ← ULog to SD card
    ├── commander start      ← State machine, arming logic
    │
    ▼
[Work Queue Scheduler]    ← Normal operation — all modules run via work queues
```

## 2. Boot Time Budget

| Phase | Max Duration | Notes |
|-------|-------------|-------|
| ROM Boot | < 5 ms | STM32H7 internal, fixed |
| PX4 Bootloader | 500–3000 ms | Configurable delay (`SYS_BL_UPDATE`), waits for USB upload |
| NuttX Kernel Init | ~20 ms | Clock tree to 480 MHz, enable caches, MPU |
| Board BSP Init | ~30 ms | GPIO, SPI/I2C/UART peripheral init |
| ROMFS Mount | ~5 ms | Linked into firmware image |
| rcS Script (all modules) | ~800 ms | Includes sensor probes, param load, module starts |
| **Total** | **~1.5–4 s** | **Power-on → sensors publishing** |

> Bootloader delay (default 3 s) is the dominant factor. Set `SYS_BL_UPDATE = 0` for fast boot in production.

## 3. Recovery / Fallback Strategy

| Scenario | Detection | Action |
|----------|-----------|--------|
| Corrupt firmware | Bootloader CRC check fails | Stay in bootloader, blink LED, wait for re-flash via USB |
| Module crash | NuttX `ASSERT()` or hardfault | Hardfault handler saves backtrace to SD, watchdog resets |
| Boot loop | arming_check watchdog counter | Commander logs `boot_count`, preflight fail |
| Missing params | `param load` finds no BSON | Load compiled-in defaults, continue boot |
| SD card failure | Mount fails | Continue boot without logging, log to RAM buffer |
| Sensor not found | Driver probe returns -ENODEV | Module exits, other sensors continue, EKF2 degrades |

## 4. Watchdog Configuration

| Parameter | Value |
|-----------|-------|
| Watchdog Type | IWDG (Independent Watchdog) |
| Timeout | 10000 ms (10 s) |
| Feed Location | NuttX idle loop (`up_idle()`) |
| Early Warning | None (IWDG has no early warning IRQ) |
| Hardfault Handler | Saves registers + stack to `/fs/microsd/fault_*.log` |

## 5. Startup Script Key Files

| File | Purpose |
|------|---------|
| `ROMFS/px4fmu_common/init.d/rcS` | Master startup script |
| `ROMFS/px4fmu_common/init.d/rc.autostart` | Selects airframe config by `SYS_AUTOSTART` param |
| `ROMFS/px4fmu_common/init.d/rc.sensors` | Sensor driver start commands |
| `ROMFS/px4fmu_common/init.d/rc.mc_defaults` | Multicopter default params |
| `boards/px4/fmu-v6x/init/rc.board_defaults` | Board-specific overrides |

## 6. Cross-References

- Memory partition → [Memory-Partition.md](Memory-Partition.md)
- Firmware architecture → [Firmware-Architecture.md](Firmware-Architecture.md)
- Security decisions → [02-System-Architecture/ADR/](../02-System-Architecture/ADR/ADR-Index.md)

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
