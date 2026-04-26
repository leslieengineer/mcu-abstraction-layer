---
title: "Memory Map"
type: document
doc-id: IF-MEM
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# Memory Map

> Complete address space for the STM32H753 (Pixhawk FMU-v6X) and external memory.

## 1. MCU Internal Memory Map

| Start Address | End Address | Size | Region | Access | Description |
|--------------|------------|------|--------|--------|-------------|
| `0x08000000` | `0x081FFFFF` | 2 MB | Flash | RX | Application code (dual-bank) |
| `0x00000000` | `0x0000FFFF` | 64 KB | ITCM RAM | RX | Instruction cache (fast exec) |
| `0x20000000` | `0x2001FFFF` | 128 KB | DTCM RAM | RW | Stack, critical data (zero-wait) |
| `0x24000000` | `0x2407FFFF` | 512 KB | AXI SRAM | RW | Main data, DMA buffers, heap |
| `0x30000000` | `0x3001FFFF` | 128 KB | SRAM1+2 | RW | DMA-accessible buffers |
| `0x38000000` | `0x3800FFFF` | 64 KB | SRAM4 | RW | Backup SRAM (domain D3) |
| `0x40000000` | `0x5FFFFFFF` | — | Peripherals | RW | MMIO registers (APB1–AHB4) |

## 2. Flash Partition Layout

| Partition | Start | Size | Purpose | Writable at Runtime |
|-----------|-------|------|---------|-------------------|
| Bootloader (BL) | `0x08000000` | 32 KB | PX4 bootloader (bl_fmu-v6x) | No |
| Application (FW) | `0x08008000` | ~1920 KB | PX4 firmware image | No (firmware upload only) |
| Parameters (BSON) | Last 32 KB of flash | 32 KB | `param save` persistent storage | Yes (erase+write) |
| Board Config | `0x081FC000` | 16 KB | Board-specific calibration | Factory only |

> **Note**: PX4 uses a single firmware slot (no A/B OTA on STM32H7). Firmware update is via bootloader + USB/MAVLink upload.

## 3. External Memory Map

| Device | Interface | Start Addr | Size | Purpose |
|--------|-----------|-----------|------|---------|
| MicroSD Card | SDIO (SDMMC1) | Filesystem (FAT32) | 4–32 GB | ULog flight logs, ROMFS overlay, param backup |
| SPI NOR Flash (W25Q128) | SPI (optional) | `0x00000000` (QSPI mapped) | 16 MB | Spare parameter/log storage |

## 4. MMIO Register Summary

> Key peripheral base addresses on STM32H753. Full register details in ST reference manual RM0433.

| Peripheral | Base Address | IRQ | DMA Channel | Notes |
|-----------|-------------|-----|-------------|-------|
| SPI1 (IMU #1) | `0x40013000` | IRQ35 | DMA1_Stream0/1 | ICM-42688P, 24 MHz |
| SPI4 (IMU #2) | `0x40013400` | IRQ84 | DMA2_Stream0/1 | BMI088, 10 MHz |
| SPI2 (Baro) | `0x40003800` | IRQ36 | DMA1_Stream2 | BMP388 ×2 |
| I2C4 (Mag) | `0x58001C00` | IRQ95/96 | BDMA_Channel0 | IST8310, 400 kHz |
| USART2 (TELEM1) | `0x40004400` | IRQ38 | DMA1_Stream5/6 | MAVLink, 921600 |
| USART3 (GPS) | `0x40004800` | IRQ39 | DMA1_Stream3/4 | UBX, 115200 |
| FDCAN1 | `0x4000A000` | IRQ19/20 | — | DroneCAN bus 1 |
| FDCAN2 | `0x4000A400` | IRQ21/22 | — | CAN bus 2 |
| SDMMC1 | `0x52007000` | IRQ49 | IDMA | MicroSD card |
| USB_OTG_FS | `0x40080000` | IRQ101 | — | NSH console, firmware upload |
| TIM1 | `0x40010000` | IRQ25–27 | — | FMU PWM aux outputs |
| ADC1 | `0x40022000` | IRQ18 | DMA2_Stream4 | Battery V/I measurement |

## 5. Cross-References

- Pin assignments → [Pin-Assignment.md](Pin-Assignment.md)
- Firmware partition management → [05-Firmware-Design/Memory-Partition.md](../05-Firmware-Design/Memory-Partition.md)

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
