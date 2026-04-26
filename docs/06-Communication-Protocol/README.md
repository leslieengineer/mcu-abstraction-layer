---
title: "Communication & Protocol"
type: readme
folder: 06-Communication-Protocol
---

# 06 — Communication & Protocol

> All protocol stacks, message formats, and external interface control.
> This folder was missing in many embedded projects — leading to "tribal knowledge" about protocols.

## Contents

| File | Purpose |
|------|---------|
| [Protocol-Overview.md](Protocol-Overview.md) | Protocol stack, selection rationale |
| [Message-Format.md](Message-Format.md) | Frame structure, field definitions, encoding |
| [Interface-Control-Document.md](Interface-Control-Document.md) | ICD — contracts with external systems |

## Typical Embedded Protocols

| Layer | PX4 Choice | Alternatives |
|-------|------------|-------------|
| GCS Link | **MAVLink 2.0** over UDP/UART | DroneCAN Parameter, ROS2 topics |
| Peripheral Bus | **DroneCAN (UAVCAN v0)** over CAN | PWM, SBUS, serial ESC |
| Companion Computer | **XRCE-DDS** (Micro ROS2 bridge) | MAVLink, custom serial |
| Telemetry Radio | **MAVLink 2.0** over SiK radio / Wi-Fi | LTE modem, LoRa |
| Sensor Bus | SPI / I2C (hardware-level) | — |
