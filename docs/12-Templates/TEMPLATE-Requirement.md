---
title: "TEMPLATE — Requirement"
type: template
template-for: Requirement
---

# Requirement: {{REQ_TITLE}}

## Metadata

| Field | Value |
|-------|-------|
| Req-ID | SRS-{{TYPE}}-{{NNN}} |
| Type | Functional / Non-Functional / Interface / Constraint |
| Priority | Must / Should / Could |
| Source | PRD-{{TYPE}}-{{NNN}} / Stakeholder / Standard |
| Status | Draft / Approved / Implemented / Verified |
| Owner | {{NAME}} |

## Description

> Clear, testable requirement statement. Use "SHALL" for mandatory, "SHOULD" for recommended.

The system **SHALL** {{REQUIREMENT_STATEMENT}}.

## Rationale

> Why is this requirement needed?

{{RATIONALE}}

## Acceptance Criteria

1. {{CRITERION_1}}
2. {{CRITERION_2}}

## Constraints

- {{CONSTRAINT}}

## Traceability

| Direction | Reference |
|-----------|-----------|
| Source (upstream) | PRD-{{TYPE}}-{{NNN}} |
| Design (downstream) | SAD §{{N}}, Module: `{{module}}` |
| Test | TC-{{NNN}} |

## Change History

| Version | Date | Change | Author |
|---------|------|--------|--------|
| 0.1 | {{DATE}} | Initial draft | {{AUTHOR}} |
