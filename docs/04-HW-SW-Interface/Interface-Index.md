---
title: "Interface Index"
type: register
doc-id: IF-IDX
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# HW-SW Interface Index

> Master list of all interfaces between hardware and firmware in PX4.

## Interface Register

| IF-ID | Name | Type | HW Side | SW Side | Protocol | Doc Link |
|-------|------|------|---------|---------|----------|----------|
| IF-001 | IMU #1 (ICM-42688P) | SPI | SPI1 bus, CS=PG6 | `icm42688p` driver | SPI Mode 3, 24 MHz | [Signal-Catalog](Signal-Catalog.md#imu) |
| IF-002 | IMU #2 (BMI088) | SPI | SPI4 bus, CS=PI4/PI8 | `bmi088` driver (accel+gyro) | SPI Mode 3, 10 MHz | [Signal-Catalog](Signal-Catalog.md#imu) |
| IF-003 | Barometer (BMP388 ×2) | SPI | SPI2 bus, CS=PD15/PG7 | `bmp388` driver | SPI Mode 3, 10 MHz | [Signal-Catalog](Signal-Catalog.md#baro) |
| IF-004 | Magnetometer (IST8310) | I2C | I2C4 bus, addr 0x0E | `ist8310` driver | I2C 400 kHz | [Signal-Catalog](Signal-Catalog.md#mag) |
| IF-005 | GPS (u-blox M9N) | UART | UART3 (GPS port) | `gps` module | UBX binary, 115200 baud | [Signal-Catalog](Signal-Catalog.md#gps) |
| IF-006 | MAVLink Telemetry | UART | UART2 (TELEM1) | `mavlink` module | MAVLink 2.0, 921600 baud | [Signal-Catalog](Signal-Catalog.md#telem) |
| IF-007 | RC Input | UART | UART6 (RC port) → IO | `rc_input` module | SBUS/CRSF, 100k/420k baud | [Signal-Catalog](Signal-Catalog.md#rc) |
| IF-008 | PWM Output | PWM | IO co-processor (FMU → IO UART) | `pwm_out` module | PWM 50–400 Hz / DShot | [Signal-Catalog](Signal-Catalog.md#pwm) |
| IF-009 | CAN Bus #1 | CAN | CAN1 transceiver (TCAN330) | `uavcan` module | DroneCAN, 1 Mbps | [Signal-Catalog](Signal-Catalog.md#can) |
| IF-010 | CAN Bus #2 | CAN | CAN2 transceiver (TCAN330) | `uavcan` module | Cyphal, 1 Mbps | [Signal-Catalog](Signal-Catalog.md#can) |
| IF-011 | SD Card | SDIO | SDMMC1 peripheral | NuttX FAT driver | 4-bit SDIO, 48 MHz | [Signal-Catalog](Signal-Catalog.md#sdcard) |
| IF-012 | USB Console | USB | USB OTG FS | NuttX CDC/ACM | USB 2.0 FS | [Signal-Catalog](Signal-Catalog.md#usb) |
| IF-013 | FMU ↔ IO Link | UART | UART8 (internal) | `px4io` driver | PX4IO protocol, 1.5 Mbps | Internal only |

## Interface Types Used

| Type | Count | Notes |
|------|-------|-------|
| SPI | 4 | IMU ×3, Baro ×2 (shared buses) |
| I2C | 1 | Magnetometer (external I2C also available) |
| UART | 5 | GPS, TELEM1, TELEM2, RC, FMU-IO |
| GPIO (digital) | 12 | SPI CS pins, safety switch, LEDs |
| PWM | 8+6 | 8 main (IO) + 6 aux (FMU direct) |
| CAN | 2 | DroneCAN/Cyphal |
| SDIO | 1 | MicroSD card |
| USB | 1 | Console + firmware upload |

## Template

For new HW-SW interfaces, use: [TEMPLATE-HW-SW-Interface.md](../12-Templates/TEMPLATE-HW-SW-Interface.md)

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
