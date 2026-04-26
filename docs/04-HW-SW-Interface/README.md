---
title: "HW-SW Interface"
type: readme
folder: 04-HW-SW-Interface
---

# 04 — HW-SW Interface

> The boundary between hardware and software. This is the most critical handoff in embedded.
> Every signal, pin, and memory address that firmware touches is documented here.

## Contents

| File | Purpose |
|------|---------|
| [Interface-Index.md](Interface-Index.md) | Master list of all HW-SW interfaces |
| [Signal-Catalog.md](Signal-Catalog.md) | Signal names, directions, electrical specs |
| [Memory-Map.md](Memory-Map.md) | Full address map (peripherals, flash, RAM, MMIO) |
| [Pin-Assignment.md](Pin-Assignment.md) | MCU pin ↔ function mapping |

## Why This Folder Exists

In every embedded project, **most bugs live at the HW-SW boundary**:
- Wrong pin configuration → hardware damage or silent failure
- Wrong memory address → hard fault or data corruption
- Signal timing mismatch → intermittent bugs
- Pull-up/pull-down mismatch → floating pins

Document it once, reference it forever.
