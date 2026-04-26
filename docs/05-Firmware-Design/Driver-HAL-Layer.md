---
title: "Driver & HAL Layer"
type: document
doc-id: FW-DRV
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# Driver & HAL Layer Design

> **SRS Traceability**: This document satisfies design decomposition for:
> SRS-F-008 (EKF2 sensor fusion), SRS-F-014 (DroneCAN ESC), SRS-NF-002 (sensor sampling rates), SRS-IF-001 (SPI/I2C bus configuration).
> See [Traceability-Matrix.md](../01-Product-Scope/Traceability-Matrix.md) for full mapping.

## 1. Architecture

```
┌────────────────────────────────┐
│  Modules (EKF2, mc_rate_ctrl)  │  ← Subscribe to sensor uORB topics
├────────────────────────────────┤
│  uORB (sensor_accel, etc.)     │  ← Zero-copy topic buffers
├────────────────────────────────┤
│  PX4 Device Drivers            │  ← C++ drivers: probe, init, Run()
│  (ICM42688P, BMI088, BMP388)  │
├────────────────────────────────┤
│  NuttX Device Interface        │  ← /dev/spi-1, open/read/write/ioctl
├────────────────────────────────┤
│  NuttX HAL + Board BSP        │  ← stm32_spi.c, board_config.h
└────────────────────────────────┘
```

## 2. NuttX HAL (Peripheral Layer)

PX4 delegates peripheral access to NuttX. Board BSP configures instances.

| Module | NuttX Source | Peripherals | DMA | IRQ | Notes |
|--------|-------------|------------|-----|-----|-------|
| SPI | `stm32_spi.c` | SPI1, SPI2, SPI4 | Yes | Yes | Per-bus locking, configurable clock |
| I2C | `stm32_i2c.c` | I2C1, I2C4 | No | Yes | 400 kHz fast mode |
| UART | `stm32_serial.c` | USART2, USART3, UART7, UART8 | Yes (RX ring) | Yes | DMA circular buffer |
| GPIO | NuttX GPIO subsystem | Port A–K | — | EXTI | Configured in `board_config.h` |
| ADC | `stm32_adc.c` | ADC1 | No | No | Battery voltage/current |
| SDIO | `stm32_sdmmc.c` | SDMMC1 | IDMA | Yes | 4-bit, 48 MHz |
| CAN | `stm32_fdcan.c` | FDCAN1, FDCAN2 | — | Yes | DroneCAN / Cyphal |
| Timer | `stm32_pwm.c` | TIM1, TIM4 | — | Yes | PWM output, capture input |

## 3. PX4 Device Drivers

PX4 drivers inherit from `cdev::CDev` or `I2CSPIDriver<T>` and follow a common pattern.

| Driver Class | Device | Bus | Source Path | uORB Output | API |
|-------------|--------|-----|------------|-------------|-----|
| `ICM42688P` | ICM-42688P | SPI1 | `src/drivers/imu/invensense/icm42688p/` | `sensor_accel`, `sensor_gyro` | `init()`, `Run()`, `print_status()` |
| `BMI088` | BMI088 | SPI4 | `src/drivers/imu/bosch/bmi088/` | `sensor_accel`, `sensor_gyro` | `init()`, `Run()`, `print_status()` |
| `BMP388` | BMP388 | SPI2 | `src/drivers/barometer/bmp388/` | `sensor_baro` | `init()`, `Run()`, `collect()` |
| `IST8310` | IST8310 | I2C4 | `src/drivers/magnetometer/isentek/ist8310/` | `sensor_mag` | `init()`, `Run()`, `collect()` |
| `UBX` | u-blox M9N | UART3 | `src/drivers/gps/` | `vehicle_gps_position` | `init()`, `Run()`, `receive()` |
| `PWMOut` | FMU PWM | TIM1/4 | `src/drivers/pwm_out/` | — (subscriber) | `init()`, `Run()`, `update_pwm()` |
| `UAVCAN` | DroneCAN | FDCAN1/2 | `src/drivers/uavcan/` | Multiple | `init()`, `Run()`, `node_status()` |

## 4. Driver Pattern (`I2CSPIDriver`)

```cpp
class ICM42688P : public I2CSPIDriver<ICM42688P>
{
public:
    ICM42688P(const I2CSPIDriverConfig &config);
    ~ICM42688P() override;

    static I2CSPIDriverBase *instantiate(const I2CSPIDriverConfig &config,
                                         int runtime_instance);
    static void print_usage();

    int  init() override;       // Probe device, configure registers
    void Run() override;        // Called by work queue at DRDY rate
    void print_status() override;

private:
    void configure();           // Write sensor config registers
    bool check_whoami();        // Verify chip ID
    void process_accel(const uint8_t *buf);
    void process_gyro(const uint8_t *buf);

    uORB::PublicationMulti<sensor_accel_s> _sensor_accel_pub;
    uORB::PublicationMulti<sensor_gyro_s>  _sensor_gyro_pub;
};
```

Key rules:
1. `init()` — probe device, configure, start work queue scheduling
2. `Run()` — triggered by DRDY interrupt or periodic timer; read + publish
3. All hardware access goes through NuttX `/dev/spi-N` file operations
4. Each driver instance publishes its own uORB multi-instance topic

## 5. Error Handling Strategy

| Layer | Strategy |
|-------|----------|
| NuttX HAL | Return `-errno` (e.g., `-EIO`, `-ETIMEDOUT`); caller checks |
| PX4 Driver | Retry register read 3×, then `PX4_ERR("...")` log; continue degraded |
| Module | Check `orb_copy()` return; use stale data if fresh unavailable |
| Commander | Count consecutive sensor failures; trigger failsafe if threshold exceeds |

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
