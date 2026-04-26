---
title: "Templates"
type: readme
folder: 12-Templates
---

# 12 — Templates

> **Single source of truth** for all document templates.
> Never duplicate templates — always copy from here.

## Available Templates

| Template | Purpose | Used In |
|----------|---------|---------|
| [TEMPLATE-ADR.md](TEMPLATE-ADR.md) | Architecture Decision Record | `02-System-Architecture/ADR/` |
| [TEMPLATE-HW-SW-Interface.md](TEMPLATE-HW-SW-Interface.md) | HW-SW interface specification | `04-HW-SW-Interface/` |
| [TEMPLATE-Module-Design.md](TEMPLATE-Module-Design.md) | Firmware module design doc | `05-Firmware-Design/Module-Design/` |
| [TEMPLATE-Release-Note.md](TEMPLATE-Release-Note.md) | Release note per version | `08-Build-Release/Release-Notes/` |
| [TEMPLATE-Requirement.md](TEMPLATE-Requirement.md) | Individual requirement definition | `01-Product-Scope/` |
| [TEMPLATE-State-Machine.md](TEMPLATE-State-Machine.md) | State machine specification | `05-Firmware-Design/State-Machines/` |
| [TEMPLATE-Test-Case.md](TEMPLATE-Test-Case.md) | Individual test case | `07-Quality-Test/Test-Cases/` |

## How to Use

1. Copy the template file to the target folder
2. Rename following the naming convention in `00-Document-Control/Naming-Convention.md`
3. Fill in all `{{PLACEHOLDER}}` fields
4. Remove instruction comments (lines starting with `>`)
5. Submit for review
