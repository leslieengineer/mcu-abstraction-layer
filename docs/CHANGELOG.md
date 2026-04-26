---
title: "Documentation Changelog"
type: log
version: "1.0"
status: released
---

# Documentation Changelog

> Track all controlled document changes for audit trail.
> Format: ISO 8601 date, document ID, change summary, author.

---

## Log

| Date | Document | Change | Author | Approved By |
|------|----------|--------|--------|-------------|
| 2024-12-01 | All | Initial PX4 v1.16.1 documentation structure created | PX4 Dev Team | — |
| 2024-12-15 | SRS, PRD | Requirements baseline frozen for v1.16 | PX4 Dev Team | Release Manager |
| 2025-01-10 | SAD, SDD | Firmware architecture documented (uORB, modules, HAL) | PX4 Dev Team | — |

---

## Rules

1. Every change to a **controlled document** (any file in `00-Document-Control/Official-Document-Register.md`) MUST have an entry here
2. Use the document's short ID (e.g., `PRD`, `SRS`, `SAD`)
3. If a document is moved to `99-Archive/`, record it here with reason
4. This file is append-only — never delete entries
