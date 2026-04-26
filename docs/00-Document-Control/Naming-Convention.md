---
title: "Naming Convention"
type: document
doc-id: DOC-NAM
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# Naming Convention

## 1. Folder Names

```
XX-Category-Name/
```

- **XX**: Two-digit prefix (`00`–`99`) for sort order
- **Category-Name**: PascalCase with hyphens, no spaces
- Examples: `00-Document-Control`, `05-Firmware-Design`, `99-Archive`

## 2. Document Files

```
Purpose-Description.md
```

- PascalCase with hyphens
- No spaces, no underscores in file names
- Examples: `Firmware-Architecture.md`, `Risk-Register.md`

## 3. Official Controlled Documents

```
{{PROJECT_CODE}}-XXX-Full-Title.md
```

- **PROJECT_CODE**: Short project identifier (e.g., `PX4`)
- **XXX**: Standard abbreviation (see table below)

| Code | Document Type |
|------|--------------|
| PRD | Product Requirements Document |
| SRS | Software Requirements Specification |
| SAD | Software Architecture Document |
| SDD | Software Design Description |
| ICD | Interface Control Document |
| STP | Software Test Plan |
| STD | Software Test Description |
| STR | Software Test Report |
| BRP | Build & Release Plan |
| RMP | Risk Management Plan |
| CMP | Compliance Matrix |
| OPS | Operations & Support Guide |

## 4. Architecture Decision Records

```
ADR-NNNN-short-description.md
```

- **NNNN**: Four-digit sequential number
- **short-description**: lowercase, hyphen-separated
- Example: `ADR-0001-adc-chip-selection.md`

## 5. Templates

```
TEMPLATE-Purpose.md
```

- Always prefixed with `TEMPLATE-`
- Located exclusively in `12-Templates/`

## 6. Companion Files

| Format | Location | Naming |
|--------|----------|--------|
| `.drawio` | `Companion-Formats/diagrams-drawio/` | `description.drawio` |
| `.puml` | `Companion-Formats/uml-puml/` | `description.puml` |
| `.csv` | `Companion-Formats/matrices-csv/` | `description.csv` |
| `.xlsx` / `.xlsx.spec.md` | `Companion-Formats/registers-xlsx/` | `description.xlsx` |
| `.pdf` | `Companion-Formats/exports-pdf/` | `DOC-ID-vX.Y.pdf` |

## 7. Release Notes

```
RELEASE-vX.Y.Z-YYYY-MM-DD.md
```

- Example: `RELEASE-v1.2.0-2026-04-11.md`

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
