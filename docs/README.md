---
title: "PX4 Autopilot — Project Documentation"
type: readme
project: "PX4"
version: "1.0"
created: "2024-12-01"
owner: "Dronecode Foundation / Linux Foundation"
status: released
---

# PX4 — Project Documentation

> **One-line description**: This document aims to document the progress of creating an abstraction layer for all MCUs, apply the polymorphism of OOP.

---

## Quick Navigation

| # | Section | Purpose | Status |
|---|---------|---------|--------|
| [00](00-Document-Control/README.md) | Document Control | Governance, naming, registers | ✅ |
| [01](01-Product-Scope/README.md) | Product & Scope | Charter, PRD, SRS, traceability | ✅ |
| [02](02-System-Architecture/README.md) | System Architecture | Context, ADR | ✅ |
| [03](03-Hardware/README.md) | Hardware | Pixhawk boards, sensors, datasheets | ✅ |
| [04](04-HW-SW-Interface/README.md) | HW-SW Interface | uORB signals, memory map, pins | ✅ |
| [05](05-Firmware-Design/README.md) | Firmware Design | Architecture, modules, HAL, coding | ✅ |
| [06](06-Communication-Protocol/README.md) | Communication & Protocol | MAVLink, uORB, DroneCAN, DDS | ✅ |
| [07](07-Quality-Test/README.md) | Quality & Test | SITL, HITL, unit test, CI/CD | ✅ |
| [08](08-Build-Release/README.md) | Build & Release | CMake, Kconfig, versioning | ✅ |
| [09](09-Project-Management/README.md) | Project Management | Risk, decisions, glossary | ✅ |
| [10](10-Operations-Support/README.md) | Operations & Support | NSH diagnostics, flight review | ✅ |
| [11](11-AI-Governance/README.md) | AI Governance | Safety-critical AI review rules | ✅ |
| [12](12-Templates/README.md) | Templates | All document templates | ✅ |
| [99](99-Archive/README.md) | Archive | Deprecated documents | — |

> **Legend**: 🔲 Not started · 🔶 In progress · ✅ Complete · — N/A

---

## Project Metadata

| Field | Value |
|-------|-------|
| Project Code | `PX4` |
| Product Name | PX4 Autopilot |
| Version | v1.16.1 |
| Target MCU | STM32H7 / STM32F7 (ARM Cortex-M7), STM32F4 (Cortex-M4) |
| RTOS | NuttX 12.x (primary), POSIX (SITL), QURT (Snapdragon) |
| Key Standards | MAVLink 2.0, DroneCAN/Cyphal, DO-178C (reference), BSD-3-Clause |
| Repository | https://github.com/PX4/PX4-Autopilot |
| Organization | Dronecode Foundation / Linux Foundation |
| Start Date | 2011 (ETH Zürich PIXHAWK project) |

---

## How to Use This Vault

1. **Start reading**: Open the folder matching your concern (e.g., `05-Firmware-Design/`)
2. **Create new docs**: Use templates from `12-Templates/`
3. **Record decisions**: Architecture → `02-System-Architecture/ADR/`, Other → `09-Project-Management/Decision-Log.md`
4. **Track changes**: Update `CHANGELOG.md` for every controlled document change
5. **Archive**: Move superseded docs to `99-Archive/`, never delete

---

## Key Documents (Quick Links)

- [Project Charter](01-Product-Scope/Project-Charter.md)
- [Product Requirements (PRD)](01-Product-Scope/Product-Requirements.md)
- [System Context](02-System-Architecture/System-Context.md)
- [Firmware Architecture](05-Firmware-Design/Firmware-Architecture.md)
- [Test Plan](07-Quality-Test/Test-Plan.md)
- [Risk Register](09-Project-Management/Risk-Register.md)
- [Glossary](09-Project-Management/Glossary.md)


---


# Embedded Project Documentation Standard

> **Mục đích**: Chuẩn hóa cách trình bày tài liệu cho tất cả dự án embedded system.
> Copy thư mục `Project-Template/` làm khung cho mỗi dự án mới.

---

## Quick Start — Cách dùng

1. Copy toàn bộ `Project-Template/` vào vị trí dự án mới
2. Rename folder root thành `<PROJECT-CODE>/` (ví dụ: `ENAMV2/`)
3. Mở `README.md` trong project, cập nhật metadata
4. Xóa/bỏ các folder không dùng → ghi chú lý do trong `CHANGELOG.md`
5. Bắt đầu viết tài liệu theo template có sẵn trong `12-Templates/`

---

## Design Principles — Nguyên tắc thiết kế

| # | Principle | Giải thích |
|---|-----------|-----------|
| 1 | **Human + AI readable** | YAML frontmatter + Markdown thuần. Mọi tool đều parse được |
| 2 | **Single source of truth** | Mỗi artifact chỉ tồn tại 1 file. Cross-reference bằng link |
| 3 | **Number-prefixed folders** | `00-` → `99-` đảm bảo thứ tự cố định trong mọi file explorer |
| 4 | **Templates centralized** | Tất cả template ở `12-Templates/`, tránh drift |
| 5 | **HW + SW đều có folder** | Embedded = hardware + software. Cả hai phải được document |
| 6 | **Companion formats tách biệt** | drawio, csv, puml → riêng folder, không lẫn với Markdown |
| 7 | **No personal in project** | Ghi chú cá nhân KHÔNG nằm trong cây tài liệu dự án |

---

## Full Directory Tree

```
Project-Template/
├── README.md                                    # Project overview & navigation
├── CHANGELOG.md                                 # Documentation changelog (audit trail)
│
├── 00-Document-Control/                         # Governance, naming, registers
│   ├── README.md
│   ├── Document-Governance-Rules.md             # Review/approval/versioning rules
│   ├── Naming-Convention.md                     # File & artifact naming standard
│   ├── Official-Document-Register.md            # Master list of all controlled docs
│   └── Companion-Formats/                       # Non-Markdown companion files
│       ├── README.md
│       ├── diagrams-drawio/                     # .drawio architecture diagrams
│       ├── exports-pdf/                         # Baseline PDF exports
│       ├── matrices-csv/                        # CSV traceability/risk matrices
│       ├── registers-xlsx/                      # Excel workbooks & specs
│       └── uml-puml/                            # PlantUML sequence/class diagrams
│
├── 01-Product-Scope/                            # What are we building & why
│   ├── README.md
│   ├── Project-Charter.md                       # Project purpose, stakeholders, scope
│   ├── Product-Requirements.md                  # PRD — high-level product requirements
│   ├── Requirements-Baseline.md                 # Approved SRS baseline snapshot
│   └── Traceability-Matrix.md                   # Req → Design → Test mapping
│
├── 02-System-Architecture/                      # System-level design decisions
│   ├── README.md
│   ├── System-Context.md                        # C4 context & container diagrams
│   └── ADR/                                     # Architecture Decision Records
│       └── ADR-Index.md                         # Index of all ADRs
│
├── 03-Hardware/                                 # Hardware documentation & references
│   ├── README.md
│   ├── Hardware-Overview.md                     # Block diagram, key specs
│   ├── Schematic-Revision-Log.md                # Schematic version history
│   ├── BOM-Management.md                        # Bill of materials tracking
│   └── Component-Datasheet-Index.md             # Datasheet links & key parameters
│
├── 04-HW-SW-Interface/                          # Boundary between HW and SW
│   ├── README.md
│   ├── Interface-Index.md                       # Master list of all interfaces
│   ├── Signal-Catalog.md                        # Signal names, directions, specs
│   ├── Memory-Map.md                            # Address map (peripherals, flash, RAM)
│   └── Pin-Assignment.md                        # MCU pin ↔ function mapping
│
├── 05-Firmware-Design/                          # Firmware/software design details
│   ├── README.md
│   ├── Firmware-Architecture.md                 # Layered architecture, RTOS config
│   ├── Boot-Sequence.md                         # Power-on → application-ready flow
│   ├── Memory-Partition.md                      # Flash/RAM partition table
│   ├── Driver-HAL-Layer.md                      # Driver & HAL design overview
│   ├── Coding-Standard.md                       # C/C++ rules, MISRA subset, DbC
│   ├── Module-Design/                           # Per-module design docs
│   │   └── README.md
│   └── State-Machines/                          # State machine specifications
│       └── README.md
│
├── 06-Communication-Protocol/                   # Protocols & message formats
│   ├── README.md
│   ├── Protocol-Overview.md                     # Stack diagram, protocol selection
│   ├── Message-Format.md                        # Frame structure, field definitions
│   └── Interface-Control-Document.md            # ICD — external system interfaces
│
├── 07-Quality-Test/                             # Verification, validation, compliance
│   ├── README.md
│   ├── VnV-Strategy.md                          # V&V approach, coverage targets
│   ├── Test-Plan.md                             # STP — master test plan
│   ├── Defect-Taxonomy-RCA.md                   # Defect classification & root cause
│   ├── Compliance-Matrix.md                     # Standard compliance evidence
│   └── Test-Cases/                              # Individual test case files
│       └── README.md
│
├── 08-Build-Release/                            # CI/CD, versioning, release process
│   ├── README.md
│   ├── Build-Release-Process.md                 # Build pipeline, release gates
│   ├── Versioning-Branching.md                  # SemVer rules, branch strategy
│   └── Release-Notes/                           # Per-release notes
│       └── README.md
│
├── 09-Project-Management/                       # Risk, decisions, glossary
│   ├── README.md
│   ├── Risk-Register.md                         # Risk ID, impact, mitigation
│   ├── Decision-Log.md                          # Non-architecture decisions
│   └── Glossary.md                              # Project-specific terminology
│
├── 10-Operations-Support/                       # Post-deployment & field support
│   ├── README.md
│   ├── Diagnostics.md                           # Logging, metrics, health checks
│   └── Field-Issue-Playbook.md                  # Troubleshooting runbooks
│
├── 11-AI-Governance/                            # Rules for AI-assisted development
│   ├── README.md
│   ├── AI-Mandatory-Rules.md                    # Hard constraints for AI agents
│   └── AI-Code-Review-Checklist.md              # AI-generated code review criteria
│
├── 12-Templates/                                # All document templates (single source)
│   ├── README.md
│   ├── TEMPLATE-ADR.md
│   ├── TEMPLATE-HW-SW-Interface.md
│   ├── TEMPLATE-Module-Design.md
│   ├── TEMPLATE-Release-Note.md
│   ├── TEMPLATE-Requirement.md
│   ├── TEMPLATE-State-Machine.md
│   └── TEMPLATE-Test-Case.md
│
└── 99-Archive/                                  # Deprecated/superseded documents
    └── README.md
```

---

## Folder Overview

| Folder | Nội dung | Mapped Standard |
|--------|---------|-----------------|
| `00-Document-Control` | Governance rules, naming, registers, companion formats | ISO 9001, CMMI CM |
| `01-Product-Scope` | Charter, PRD, SRS baseline, traceability | IEEE 830, IEEE 29148 |
| `02-System-Architecture` | Context diagrams, ADR | ISO 42010, C4 Model |
| `03-Hardware` | HW overview, schematic, BOM, datasheets | IPC-2581 |
| `04-HW-SW-Interface` | Signal, memory map, pin assignment | IEEE 1471 |
| `05-Firmware-Design` | Architecture, modules, boot, HAL, coding rules | IEEE 1016 (SDD) |
| `06-Communication-Protocol` | Protocol stack, message format, ICD | IEEE 1003, MIL-STD-1553 |
| `07-Quality-Test` | V&V, test plan, defect RCA, compliance | IEEE 829, IEEE 1012 |
| `08-Build-Release` | CI/CD, versioning, release notes | SemVer, GitFlow |
| `09-Project-Management` | Risk register, decision log, glossary | ISO 31000, PMBOK |
| `10-Operations-Support` | Diagnostics, field issue playbook | ITIL |
| `11-AI-Governance` | AI rules, code review checklist | Internal |
| `12-Templates` | All templates (single source of truth) | — |
| `99-Archive` | Deprecated / superseded docs | — |

---

## Standards Referenced

- **IEEE 830 / 29148** — Software Requirements Specification
- **IEEE 1016** — Software Design Description
- **IEEE 829** — Software Test Documentation
- **IEEE 1012** — Verification & Validation
- **ISO 42010** — Architecture Description
- **ISO 9001** — Quality Management (Document Control)
- **ISO 31000** — Risk Management
- **IEC 62304** — Medical Device Software (lifecycle reference)
- **MISRA C** — Coding Standard subset
- **C4 Model** — Architecture visualization

---

## Version History

| Version | Date | Author | Change |
|---------|------|--------|--------|
| 1.0 | 2026-04-11 | Leslie | Initial standard release |

