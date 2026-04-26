---
title: "Official Document Register"
type: register
doc-id: DOC-REG
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# Official Document Register

> Single master list of all controlled documents in the project.
> Only documents listed here are subject to formal change control.

## Register

| Doc-ID | Title | Location | Version | Status | Owner | Last Updated |
|--------|-------|----------|---------|--------|-------|-------------|
| DOC-GOV | Document Governance Rules | `00-Document-Control/` | 1.0 | Released | PX4 Dev Team | 2024-12-01 |
| DOC-NAM | Naming Convention | `00-Document-Control/` | 1.0 | Released | PX4 Dev Team | 2024-12-01 |
| DOC-REG | Official Document Register | `00-Document-Control/` | 1.0 | Released | PX4 Dev Team | 2024-12-01 |
| CHARTER | Project Charter | `01-Product-Scope/` | 1.0 | Released | Dronecode | 2024-12-01 |
| PRD | Product Requirements Document | `01-Product-Scope/` | 1.0 | Released | PX4 Dev Team | 2024-12-01 |
| SRS | Requirements Baseline (SRS) | `01-Product-Scope/` | 1.0 | Released | PX4 Dev Team | 2024-12-15 |
| RTM | Traceability Matrix | `01-Product-Scope/` | 1.0 | Released | PX4 Dev Team | 2024-12-15 |
| SAD | System Context & Architecture | `02-System-Architecture/` | 1.0 | Released | PX4 Dev Team | 2025-01-10 |
| HW-OVR | Hardware Overview | `03-Hardware/` | 1.0 | Released | PX4 Dev Team | 2025-01-10 |
| HW-BOM | BOM Management | `03-Hardware/` | 1.0 | Released | PX4 Dev Team | 2025-01-10 |
| HW-DSI | Component Datasheet Index | `03-Hardware/` | 1.0 | Released | PX4 Dev Team | 2025-01-10 |
| HW-SCH | Schematic Revision Log | `03-Hardware/` | 1.0 | Released | PX4 Dev Team | 2025-01-10 |
| IF-IDX | Interface Index | `04-HW-SW-Interface/` | 1.0 | Released | PX4 Dev Team | 2025-01-10 |
| IF-SIG | Signal Catalog | `04-HW-SW-Interface/` | 1.0 | Released | PX4 Dev Team | 2025-01-10 |
| IF-MEM | Memory Map | `04-HW-SW-Interface/` | 1.0 | Released | PX4 Dev Team | 2025-01-10 |
| IF-PIN | Pin Assignment | `04-HW-SW-Interface/` | 1.0 | Released | PX4 Dev Team | 2025-01-10 |
| SDD-ARCH | Firmware Architecture | `05-Firmware-Design/` | 1.0 | Released | PX4 Dev Team | 2025-01-10 |
| FW-BOOT | Boot Sequence | `05-Firmware-Design/` | 1.0 | Released | PX4 Dev Team | 2025-01-10 |
| FW-COD | Coding Standard | `05-Firmware-Design/` | 1.0 | Released | PX4 Dev Team | 2025-01-10 |
| FW-DRV | Driver & HAL Layer | `05-Firmware-Design/` | 1.0 | Released | PX4 Dev Team | 2025-01-10 |
| FW-MEM | Memory Partition | `05-Firmware-Design/` | 1.0 | Released | PX4 Dev Team | 2025-01-10 |
| COM-OVR | Protocol Overview | `06-Communication-Protocol/` | 1.0 | Released | PX4 Dev Team | 2025-01-10 |
| COM-MSG | Message Format Specification | `06-Communication-Protocol/` | 1.0 | Released | PX4 Dev Team | 2025-01-10 |
| ICD | Interface Control Document | `06-Communication-Protocol/` | 1.0 | Released | PX4 Dev Team | 2025-01-10 |
| VNV | Verification & Validation Strategy | `07-Quality-Test/` | 1.0 | Released | PX4 Dev Team | 2025-01-15 |
| STP | Test Plan | `07-Quality-Test/` | 1.0 | Released | PX4 Dev Team | 2025-01-15 |
| CMP | Compliance Matrix | `07-Quality-Test/` | 1.0 | Released | PX4 Dev Team | 2025-01-15 |
| QA-RCA | Defect Taxonomy & Root Cause Analysis | `07-Quality-Test/` | 1.0 | Released | PX4 Dev Team | 2025-01-15 |
| BRP | Build & Release Process | `08-Build-Release/` | 1.0 | Released | PX4 Dev Team | 2025-01-10 |
| BRP-VER | Versioning & Branching Strategy | `08-Build-Release/` | 1.0 | Released | PX4 Dev Team | 2025-01-10 |
| RMP | Risk Register | `09-Project-Management/` | 1.0 | Released | PX4 Dev Team | 2025-01-15 |
| PM-DEC | Decision Log | `09-Project-Management/` | 1.0 | Released | PX4 Dev Team | 2025-01-15 |
| PM-GLO | Glossary | `09-Project-Management/` | 1.0 | Released | PX4 Dev Team | 2025-01-15 |
| OPS-DIAG | Diagnostics & Observability | `10-Operations-Support/` | 1.0 | Released | PX4 Dev Team | 2025-01-15 |
| OPS-FIP | Field Issue Investigation Playbook | `10-Operations-Support/` | 1.0 | Released | PX4 Dev Team | 2025-01-15 |
| AI-MAN | AI Agent Mandatory Rules | `11-AI-Governance/` | 1.0 | Released | PX4 Dev Team | 2025-01-15 |
| AI-CHK | AI Code Review Checklist | `11-AI-Governance/` | 1.0 | Released | PX4 Dev Team | 2025-01-15 |

## Rules

1. **Every new controlled document** must be added to this register before review
2. **Version** and **Status** must match the document's frontmatter
3. **Last Updated** uses ISO 8601 format (`YYYY-MM-DD`)
4. Archived documents are marked as `Archived` in Status, not removed from register
