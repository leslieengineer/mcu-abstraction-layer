---
title: "Firmware Design"
type: readme
folder: 05-Firmware-Design
---

# 05 — Firmware Design

> The largest section in an embedded project. Covers architecture, modules, boot, HAL, and coding rules.

## Contents

| File | Purpose | IEEE Ref |
|------|---------|----------|
| [Firmware-Architecture.md](Firmware-Architecture.md) | Layered architecture, RTOS config, task model | IEEE 1016 |
| [Boot-Sequence.md](Boot-Sequence.md) | Power-on → application-ready flow | — |
| [Memory-Partition.md](Memory-Partition.md) | Flash/RAM partition table & OTA layout | — |
| [Driver-HAL-Layer.md](Driver-HAL-Layer.md) | Driver & HAL design overview | — |
| [Coding-Standard.md](Coding-Standard.md) | C/C++ rules, MISRA subset, Design by Contract | MISRA C |
| [Module-Design/](Module-Design/README.md) | Per-module detailed design docs | IEEE 1016 |
| [State-Machines/](State-Machines/README.md) | State machine specifications | — |

## Architecture Layers

```
┌─────────────────────────────────────────────────────┐
│  Application  │ Commander │ EKF2 │ Navigator │ MC/FW │  ← Flight logic
├─────────────────────────────────────────────────────┤
│  Modules      │ Control Alloc │ Logger │ MAVLink    │  ← Service modules
├─────────────────────────────────────────────────────┤
│  uORB + Work Queue Manager                          │  ← IPC + scheduling
├─────────────────────────────────────────────────────┤
│  Drivers      │ IMU │ Baro │ Mag │ GPS │ PWM │ CAN │  ← Sensor/actuator
├─────────────────────────────────────────────────────┤
│  NuttX RTOS   │ POSIX API │ Board BSP              │  ← OS + HAL
└─────────────────────────────────────────────────────┘
```

## Reading Order

1. Firmware Architecture → overall picture
2. Boot Sequence → how the system starts
3. Memory Partition → where things live in flash/RAM
4. Driver/HAL → how firmware talks to hardware
5. Module Design → deep dive per module
6. State Machines → behavioral specifications
