---
title: "TEMPLATE — HW-SW Interface"
type: template
template-for: HW-SW-Interface
---

# HW-SW Interface: {{INTERFACE_NAME}}

## Overview

| Field | Value |
|-------|-------|
| Interface ID | IF-{{NNN}} |
| Type | SPI / I2C / UART / GPIO / ADC / PWM |
| HW Component | {{COMPONENT}} ({{PART_NUMBER}}) |
| SW Module | `{{module_name}}` |
| Schematic Sheet | {{SHEET_REF}} |
| Owner | {{NAME}} |

## Physical Connection

| Signal | MCU Pin | Direction | Voltage | Pull | Notes |
|--------|---------|-----------|---------|------|-------|
| {{SIG}} | {{PIN}} | In / Out | {{V}} | Up / Down / None | — |

## Protocol Configuration

| Parameter | Value |
|-----------|-------|
| Clock Speed | {{FREQ}} |
| Mode / Polarity | {{MODE}} |
| Bit Order | MSB / LSB first |
| Word Size | {{BITS}} bits |

## Register / Command Interface

| Register/Cmd | Address | R/W | Description | Reset Value |
|-------------|---------|-----|-------------|-------------|
| {{REG}} | `0x{{ADDR}}` | R / W / RW | {{DESCRIPTION}} | `0x{{VAL}}` |

## Timing Requirements

| Parameter | Min | Typical | Max | Unit |
|-----------|-----|---------|-----|------|
| {{PARAM}} | {{MIN}} | {{TYP}} | {{MAX}} | {{UNIT}} |

## Error Handling

| Error Condition | Detection | Recovery |
|----------------|-----------|----------|
| No response | Timeout ({{ms}} ms) | Retry {{N}} times, then report |
| CRC mismatch | CRC check | Retry |
| Unexpected data | Range check | Log + discard |

## Firmware API

```c
status_t {{module}}_init(void);
status_t {{module}}_read(uint8_t reg, uint8_t *data, size_t len);
status_t {{module}}_write(uint8_t reg, const uint8_t *data, size_t len);
```
