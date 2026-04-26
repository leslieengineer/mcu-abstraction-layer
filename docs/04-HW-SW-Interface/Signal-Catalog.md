---
title: "Signal Catalog"
type: document
doc-id: IF-SIG
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# Signal Catalog

> Every signal that crosses the HW-SW boundary in PX4 Pixhawk v6X.

## Signals

### IMU {#imu}

| Signal Name | Direction | Type | Voltage | Frequency / Rate | Pull | Active Level | Connected To | Notes |
|-------------|-----------|------|---------|-----------------|------|-------------|-------------|-------|
| SPI1_SCK | Out | Digital | 3.3 V | 24 MHz | None | — | ICM-42688P.SCK | IMU #1 clock |
| SPI1_MOSI | Out | Digital | 3.3 V | 24 MHz | None | — | ICM-42688P.SDI | IMU #1 data out |
| SPI1_MISO | In | Digital | 3.3 V | 24 MHz | None | — | ICM-42688P.SDO | IMU #1 data in |
| IMU1_CS | Out | Digital | 3.3 V | — | Up | Low | ICM-42688P.CS | Active-low chip select |
| IMU1_DRDY | In | Digital | 3.3 V | 8 kHz | None | High | ICM-42688P.INT1 | Data-ready interrupt |
| SPI4_SCK | Out | Digital | 3.3 V | 10 MHz | None | — | BMI088.SCK | IMU #2 clock |
| BMI088_ACCEL_CS | Out | Digital | 3.3 V | — | Up | Low | BMI088.CSB1 | Accel chip select |
| BMI088_GYRO_CS | Out | Digital | 3.3 V | — | Up | Low | BMI088.CSB2 | Gyro chip select |
| BMI088_DRDY | In | Digital | 3.3 V | 2 kHz | None | High | BMI088.INT1 | Data-ready interrupt |

### Barometer {#baro}

| Signal Name | Direction | Type | Voltage | Frequency / Rate | Pull | Active Level | Connected To | Notes |
|-------------|-----------|------|---------|-----------------|------|-------------|-------------|-------|
| BARO1_CS | Out | Digital | 3.3 V | — | Up | Low | BMP388 #1.CSB | Primary baro select |
| BARO2_CS | Out | Digital | 3.3 V | — | Up | Low | BMP388 #2.CSB | Secondary baro select |

### Magnetometer {#mag}

| Signal Name | Direction | Type | Voltage | Frequency / Rate | Pull | Active Level | Connected To | Notes |
|-------------|-----------|------|---------|-----------------|------|-------------|-------------|-------|
| I2C4_SDA | Bidir | Digital | 3.3 V | 400 kHz | Up (4.7 kΩ) | — | IST8310.SDA | I2C data |
| I2C4_SCL | Out | Digital | 3.3 V | 400 kHz | Up (4.7 kΩ) | — | IST8310.SCL | I2C clock |
| MAG_DRDY | In | Digital | 3.3 V | 100 Hz | None | High | IST8310.DRDY | Data ready |

### GPS {#gps}

| Signal Name | Direction | Type | Voltage | Frequency / Rate | Pull | Active Level | Connected To | Notes |
|-------------|-----------|------|---------|-----------------|------|-------------|-------------|-------|
| UART3_TX | Out | Digital | 3.3 V | 115200 baud | None | — | u-blox.RX | GPS commands |
| UART3_RX | In | Digital | 3.3 V | 115200 baud | None | — | u-blox.TX | GPS data (UBX/NMEA) |

### Telemetry {#telem}

| Signal Name | Direction | Type | Voltage | Frequency / Rate | Pull | Active Level | Connected To | Notes |
|-------------|-----------|------|---------|-----------------|------|-------------|-------------|-------|
| UART2_TX | Out | Digital | 3.3 V | 921600 baud | None | — | Radio.RX | MAVLink out (TELEM1) |
| UART2_RX | In | Digital | 3.3 V | 921600 baud | None | — | Radio.TX | MAVLink in |
| UART2_CTS | In | Digital | 3.3 V | — | Up | Low | Radio.CTS | Flow control |
| UART2_RTS | Out | Digital | 3.3 V | — | None | Low | Radio.RTS | Flow control |

### RC Input {#rc}

| Signal Name | Direction | Type | Voltage | Frequency / Rate | Pull | Active Level | Connected To | Notes |
|-------------|-----------|------|---------|-----------------|------|-------------|-------------|-------|
| RC_INPUT | In | Digital | 3.3 V | 100 kbaud (SBUS) | Up | Inverted | RC Receiver.SBUS | Via IO co-proc |

### PWM Output {#pwm}

| Signal Name | Direction | Type | Voltage | Frequency / Rate | Pull | Active Level | Connected To | Notes |
|-------------|-----------|------|---------|-----------------|------|-------------|-------------|-------|
| MAIN_OUT1–8 | Out | Digital | 3.3 V | 50–400 Hz / DShot | None | High | ESC channels 1–8 | Via IO co-processor |
| AUX_OUT1–6 | Out | Digital | 3.3 V | 50–400 Hz / DShot | None | High | ESC/servo aux | FMU direct PWM |

### CAN Bus {#can}

| Signal Name | Direction | Type | Voltage | Frequency / Rate | Pull | Active Level | Connected To | Notes |
|-------------|-----------|------|---------|-----------------|------|-------------|-------------|-------|
| CAN1_TX | Out | Digital | 3.3 V | 1 Mbps | None | — | TCAN330 #1.TXD | DroneCAN bus 1 |
| CAN1_RX | In | Digital | 3.3 V | 1 Mbps | None | — | TCAN330 #1.RXD | DroneCAN bus 1 |
| CAN2_TX | Out | Digital | 3.3 V | 1 Mbps | None | — | TCAN330 #2.TXD | CAN bus 2 |
| CAN2_RX | In | Digital | 3.3 V | 1 Mbps | None | — | TCAN330 #2.RXD | CAN bus 2 |

### SD Card {#sdcard}

| Signal Name | Direction | Type | Voltage | Frequency / Rate | Pull | Active Level | Connected To | Notes |
|-------------|-----------|------|---------|-----------------|------|-------------|-------------|-------|
| SDMMC1_D0–D3 | Bidir | Digital | 3.3 V | 48 MHz | Up | — | MicroSD.DAT | 4-bit data |
| SDMMC1_CLK | Out | Digital | 3.3 V | 48 MHz | None | — | MicroSD.CLK | SDIO clock |
| SDMMC1_CMD | Bidir | Digital | 3.3 V | 48 MHz | Up | — | MicroSD.CMD | Command |

### USB {#usb}

| Signal Name | Direction | Type | Voltage | Frequency / Rate | Pull | Active Level | Connected To | Notes |
|-------------|-----------|------|---------|-----------------|------|-------------|-------------|-------|
| USB_DM | Bidir | Digital | 3.3 V | 12 Mbps | — | — | USB connector.D- | USB Full Speed |
| USB_DP | Bidir | Digital | 3.3 V | 12 Mbps | — | — | USB connector.D+ | USB Full Speed |

## Signal Naming Convention

```
<SUBSYSTEM>_<FUNCTION>_<DIRECTION>
```

Examples:
- `IMU1_SPI_MOSI` — IMU #1 subsystem, SPI MOSI output
- `TELEM1_UART_RX` — Telemetry 1, UART receive
- `BARO1_CS` — Barometer 1, chip select

## Timing Constraints

| Signal | Setup Time | Hold Time | Max Frequency | Notes |
|--------|-----------|-----------|--------------|-------|
| SPI1 (ICM-42688P) | 5 ns | 5 ns | 24 MHz | Mode 3 (CPOL=1, CPHA=1) |
| SPI4 (BMI088) | 8 ns | 8 ns | 10 MHz | Mode 3 |
| I2C4 (IST8310) | — | — | 400 kHz | Fast mode |
| UART3 (GPS) | — | — | 115200 baud | 8N1 |
| CAN (DroneCAN) | — | — | 1 Mbps | ISO 11898 timing |

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
