---
title: "ADR Index"
type: register
folder: ADR
created: "2026-04-26"
last-updated: "2026-04-26"
author: "Leslie"
reviewer: "Release Manager"
---

# Architecture Decision Records — Index

> Each ADR captures a significant architectural decision, its context, and consequences.
> Use template: [TEMPLATE-ADR.md](../../12-Templates/TEMPLATE-ADR.md)

## Status Legend

| Status | Meaning |
|--------|---------|
| **Proposed** | Under discussion, not yet decided |
| **Accepted** | Decision made and in effect |
| **Deprecated** | Superseded by a newer ADR |
| **Rejected** | Considered but not adopted |

## ADR Register

| ADR # | Title | Status | Date | Supersedes |
|-------|-------|--------|------|-----------|
| ADR-0001 | Why did I create this abstract layer | Accepted | 2024-04 | — |
| ADR-0002 | Use a layered GPIO abstraction with core API and chip-specific extensions | Proposed | 2026-04-26 | — |


## How to Add an ADR

1. Copy `12-Templates/TEMPLATE-ADR.md` into this folder
2. Rename to `ADR-NNNN-short-description.md` (next sequential number)
3. Fill in context, decision, consequences
4. Add entry to the register table above
5. Submit for review per `00-Document-Control/Document-Governance-Rules.md`
