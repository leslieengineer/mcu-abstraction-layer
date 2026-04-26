---
title: "Diagnostics & Observability"
type: document
doc-id: OPS-DIAG
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# Diagnostics & Observability

## 1. Log System

PX4 uses `PX4_ERR/WARN/INFO/DEBUG` macros routed to MAVLink `STATUSTEXT` + ULog + NSH console.

| Level | Usage | PX4 Example | Enabled in Release |
|-------|-------|------------|-------------------|
| ERROR | System failure, sensor loss | `[ekf2] GPS timeout` | Yes |
| WARN | Recoverable anomaly | `[batt] Low battery 20%` | Yes |
| INFO | Key state transitions | `[commander] Arming allowed` | Yes |
| DEBUG | Detailed trace | `[icm42688p] FIFO count: 128` | No (debug build only) |

### Log Output Channels

| Channel | Interface | Baud / Rate | Use Case |
|---------|-----------|-------------|----------|
| NSH console | UART7 (Debug) | 57600 | Development, factory test |
| ULog (SD card) | microSD via SDIO | ~250 KB/s | Flight data recording (primary) |
| MAVLink STATUSTEXT | TELEM1 UART2 | 57600 | GCS real-time alerts |
| MAVLink Logging | USB / TELEM | Streaming | QGC live log download |

## 2. Health Metrics

| Metric | Unit | Normal Range | Alert Threshold | Source |
|--------|------|-------------|----------------|--------|
| CPU usage | % | < 60% | > 80% | `top` command / `cpuload` uORB |
| Stack watermark | bytes | > 30% free | < 15% free | NuttX `ps` / `top` |
| Heap free | bytes | > 40 KB | < 10 KB | `free` command |
| Uptime | seconds | — | Reset detected | `uptime` / `ver all` |
| Sensor health | bitmask | All OK | Any sensor failed | `sensor_status` |
| EKF2 innovation | ratio | < 0.5 | > 1.0 (innovation test fail) | `estimator_status` uORB |
| Watchdog resets | count | 0 | > 0 | `ver hwcmp` reset cause |
| Battery voltage | V | > 3.5V/cell | < 3.3V/cell | `battery_status` uORB |

## 3. Debug Interfaces

| Interface | Access | Authentication | Capabilities |
|-----------|--------|---------------|-------------|
| NSH Console | UART7 (physical) | None | Full shell: `top`, `listener`, `param` |
| SWD / JTAG | FMU debug port (10-pin JST) | — | GDB debug, flash, core dump |
| MAVLink Shell | TELEM / USB via QGC | MAVLink session | Remote NSH commands via GCS |
| USB Console | USB-C (direct) | None | NSH + firmware upload |

## 4. Diagnostic Commands (NSH)

| Command | Description | Example |
|---------|-------------|---------|
| `top` | CPU usage per task + stack watermarks | `top` |
| `ver all` | PX4 version, NuttX version, git hash, board info | `ver all` |
| `listener <topic>` | Print uORB topic in real-time | `listener sensor_accel` |
| `sensor_status` | All sensor health + sample rates | `sensor_status` |
| `ekf2 status` | EKF2 innovation ratios + sensor fusion status | `ekf2 status` |
| `param show <name>` | Read parameter value | `param show EKF2_GPS_P_GATE` |
| `param set <name> <val>` | Set parameter (persisted to SD) | `param set EKF2_GPS_P_GATE 3.0` |
| `dmesg` | NuttX kernel log buffer (boot + error messages) | `dmesg` |
| `free` | Heap memory usage | `free` |
| `ps` | Running tasks with stack usage | `ps` |
| `reboot` | Software reboot | `reboot` |
| `hardfault_log status` | Check for stored hard-fault dump | `hardfault_log status` |

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
