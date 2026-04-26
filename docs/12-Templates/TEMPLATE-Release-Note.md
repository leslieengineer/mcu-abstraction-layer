---
title: "TEMPLATE — Release Note"
type: template
template-for: Release-Note
---

# Release v{{MAJOR}}.{{MINOR}}.{{PATCH}}

**Date**: {{YYYY-MM-DD}}
**Build**: {{BUILD_NUMBER}}
**HW Compatibility**: Rev {{HW_REV}} and later

---

## Summary

> One paragraph summarizing the release.

## New Features

| Feature | SRS Ref | Description |
|---------|---------|-------------|
| {{FEATURE}} | SRS-F-{{NNN}} | {{DESCRIPTION}} |

## Bug Fixes

| Fix | Defect Ref | Description |
|-----|-----------|-------------|
| {{FIX}} | D-{{NNN}} | {{DESCRIPTION}} |

## Known Issues

| Issue | Severity | Workaround | Target Fix |
|-------|----------|-----------|-----------|
| {{ISSUE}} | {{SEV}} | {{WORKAROUND}} | v{{X.Y.Z}} |

## Breaking Changes

> List any changes that require action from users / integrators.

- {{CHANGE}}

## Upgrade Instructions

1. {{STEP_1}}
2. {{STEP_2}}

## Test Summary

| Test Level | Total | Pass | Fail | Skip |
|-----------|-------|------|------|------|
| Unit | {{N}} | {{N}} | {{N}} | {{N}} |
| Integration | {{N}} | {{N}} | {{N}} | {{N}} |
| System | {{N}} | {{N}} | {{N}} | {{N}} |

## Approvals

| Role | Name | Date | Signature |
|------|------|------|-----------|
| Developer | {{NAME}} | {{DATE}} | — |
| Reviewer | {{NAME}} | {{DATE}} | — |
| Release Manager | {{NAME}} | {{DATE}} | — |
