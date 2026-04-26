---
title: "ADR-0009: Use dedicated ADR files for each architecture decision"
type: adr
---

# ADR-0009: Use dedicated ADR files for each architecture decision

## Status

> Proposed | Accepted | Deprecated | Rejected

Proposed

## Date

2026-04-26

## Context

The project requires a clear, consistent record of architectural decisions. A single file per ADR enables easier review, versioning, and traceability than keeping decisions scattered in spreadsheets or meeting notes.

## Decision

Create one ADR document per architectural decision using the standard template in `docs/12-Templates/TEMPLATE-ADR.md`. Store ADR files in `docs/02-System-Architecture/ADR/` and maintain a central index at `ADR-Index.md`.

## Alternatives Considered

| Option | Pros | Cons |
|--------|------|------|
| Keep decisions in a shared meeting notes file | Simple, low overhead | Hard to find, poor traceability, difficult to version-control individually |
| Use a wiki or external tool | Searchable, collaborative | External dependency, harder to keep synchronized with repo |
| **One ADR file per decision** (selected) | Clear history, easy review, consistent format | Slight overhead to create and maintain files |

## Consequences

### Positive
- Each decision has a self-contained record and status.
- Easier to link related ADRs and track superseded decisions.
- Supports review workflows and git history per decision.

### Negative
- Requires discipline to create and index new ADRs.

### Risks
- Contributors may forget to update `ADR-Index.md` when adding new ADR files.

## Related

- Supersedes: —
- Related requirements: SRS-F-NNN
- Related documents: `docs/12-Templates/TEMPLATE-ADR.md`
