---
title: "Pin Assignment"
type: document
doc-id: IF-PIN
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# Pin Assignment

> MCU pin ↔ function mapping for STM32H753 (Pixhawk FMU-v6X).
> Single source of truth for all GPIO configuration.

## Pin Table (Key Pins)

| Pin # | Port.Pin | Function | AF# | Direction | Pull | Speed | Signal Name | Connected To | Notes |
|-------|----------|----------|-----|-----------|------|-------|-------------|-------------|-------|
| — | PG11 | SPI1_SCK | AF5 | Out | None | VHigh | IMU1_SCK | ICM-42688P.SCK | 24 MHz |
| — | PD7 | SPI1_MOSI | AF5 | Out | None | VHigh | IMU1_MOSI | ICM-42688P.SDI | — |
| — | PG9 | SPI1_MISO | AF5 | In | None | VHigh | IMU1_MISO | ICM-42688P.SDO | — |
| — | PG6 | GPIO_OUT | — | Out | Up | Low | IMU1_CS | ICM-42688P.CS | Active low |
| — | PJ0 | GPIO_IN (EXTI) | — | In | None | — | IMU1_DRDY | ICM-42688P.INT1 | Rising edge |
| — | PE12 | SPI4_SCK | AF5 | Out | None | High | IMU2_SCK | BMI088.SCK | 10 MHz |
| — | PE14 | SPI4_MOSI | AF5 | Out | None | High | IMU2_MOSI | BMI088.SDI | — |
| — | PE13 | SPI4_MISO | AF5 | In | None | High | IMU2_MISO | BMI088.SDO | — |
| — | PI4 | GPIO_OUT | — | Out | Up | Low | BMI088_ACCEL_CS | BMI088.CSB1 | Active low |
| — | PI8 | GPIO_OUT | — | Out | Up | Low | BMI088_GYRO_CS | BMI088.CSB2 | Active low |
| — | PD5 | USART2_TX | AF7 | Out | None | High | TELEM1_TX | Radio.RX | MAVLink |
| — | PD6 | USART2_RX | AF7 | In | Up | High | TELEM1_RX | Radio.TX | MAVLink |
| — | PD8 | USART3_TX | AF7 | Out | None | High | GPS_TX | u-blox.RX | UBX |
| — | PD9 | USART3_RX | AF7 | In | Up | High | GPS_RX | u-blox.TX | UBX |
| — | PD0 | FDCAN1_RX | AF9 | In | None | High | CAN1_RX | TCAN330.RXD | DroneCAN |
| — | PD1 | FDCAN1_TX | AF9 | Out | None | High | CAN1_TX | TCAN330.TXD | DroneCAN |
| — | PC12 | SDMMC1_CK | AF12 | Out | None | VHigh | SD_CLK | MicroSD.CLK | 48 MHz |
| — | PD2 | SDMMC1_CMD | AF12 | Bidir | Up | VHigh | SD_CMD | MicroSD.CMD | — |

> **AF#** = Alternate Function number per STM32H753 datasheet. Check RM0433 GPIO AF table.

## Peripheral Pin Summary

### SPI

| Function | Pin | AF | Notes |
|----------|-----|-----|-------|
| SPI1_SCK | PG11 | AF5 | ICM-42688P (IMU #1) |
| SPI1_MOSI | PD7 | AF5 | IMU #1 data out |
| SPI1_MISO | PG9 | AF5 | IMU #1 data in |
| SPI1_CS (IMU1) | PG6 | GPIO | Software-controlled |
| SPI4_SCK | PE12 | AF5 | BMI088 (IMU #2) |
| SPI4_MOSI | PE14 | AF5 | IMU #2 data out |
| SPI4_MISO | PE13 | AF5 | IMU #2 data in |
| SPI2_SCK | PI1 | AF5 | BMP388 barometers |
| SPI2_MOSI | PI3 | AF5 | Baro data out |
| SPI2_MISO | PI2 | AF5 | Baro data in |

### UART

| Function | Pin | AF | Notes |
|----------|-----|-----|-------|
| USART2_TX | PD5 | AF7 | TELEM1 (MAVLink primary) |
| USART2_RX | PD6 | AF7 | TELEM1 rx |
| USART3_TX | PD8 | AF7 | GPS port |
| USART3_RX | PD9 | AF7 | GPS port |
| UART7_TX | PE8 | AF7 | TELEM2 |
| UART7_RX | PF6 | AF7 | TELEM2 |
| UART8_TX | PE1 | AF8 | FMU → IO co-processor link |
| UART8_RX | PE0 | AF8 | IO → FMU link |

### I2C

| Function | Pin | AF | Notes |
|----------|-----|-----|-------|
| I2C4_SDA | PF15 | AF4 | IST8310 magnetometer, external pull-up: 4.7 kΩ |
| I2C4_SCL | PF14 | AF4 | IST8310 magnetometer, external pull-up: 4.7 kΩ |
| I2C1_SDA | PB7 | AF4 | External I2C port, 4.7 kΩ |
| I2C1_SCL | PB6 | AF4 | External I2C port, 4.7 kΩ |

### GPIO (Discretes)

| Signal | Pin | Direction | Default State | Purpose |
|--------|-----|-----------|--------------|---------|
| SAFETY_SW | PC4 | In | Hi-Z | Safety switch input (press to arm) |
| LED_GREEN | PB0 | Out | Low | System status LED |
| LED_RED | PB1 | Out | Low | Error status LED |
| LED_BLUE | PA15 | Out | Low | Activity LED |
| POWER_SENSE | PA4 (ADC1_IN4) | In (Analog) | — | Battery voltage divider |
| CURRENT_SENSE | PA5 (ADC1_IN5) | In (Analog) | — | Battery current sensor |

## Unused Pins

| Pin | Configuration | Reason |
|-----|--------------|--------|
| Reserved GPIOs | Input pull-down | Not connected — prevent floating |

## Cross-References

- Signal electrical specs → [Signal-Catalog.md](Signal-Catalog.md)
- Schematic pin mapping → [03-Hardware/Schematic-Revision-Log.md](../03-Hardware/Schematic-Revision-Log.md)

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
