---
title: "TEMPLATE — Test Case"
type: template
template-for: Test-Case
---

# Test Case: {{TC_TITLE}}

## Metadata

| Field | Value |
|-------|-------|
| TC-ID | TC-{{NNN}} |
| SRS Requirement | SRS-F-{{NNN}} |
| Test Level | Unit / Integration / System |
| Priority | High / Medium / Low |
| Test Type | Functional / Performance / Security / Boundary |
| Environment | Host / HIL / Target |
| Author | {{NAME}} |
| Status | Draft / Ready / Passed / Failed / Blocked |

## Preconditions

1. {{PRECONDITION_1}}
2. {{PRECONDITION_2}}

## Test Setup

| Item | Configuration |
|------|--------------|
| Hardware | {{HW_SETUP}} |
| Firmware Version | v{{X.Y.Z}} |
| Test Equipment | {{EQUIPMENT}} |
| Test Data | {{DATA_SOURCE}} |

## Test Steps

| Step | Action | Expected Result | Pass/Fail |
|------|--------|----------------|-----------|
| 1 | {{ACTION}} | {{EXPECTED}} | ⬜ |
| 2 | {{ACTION}} | {{EXPECTED}} | ⬜ |
| 3 | {{ACTION}} | {{EXPECTED}} | ⬜ |

## Test Data

| Input | Expected Output | Tolerance |
|-------|----------------|-----------|
| {{INPUT}} | {{OUTPUT}} | ±{{TOL}} |

## Postconditions

> State of the system after test execution.

1. {{POSTCONDITION}}

## Execution Record

| Run # | Date | Tester | FW Version | Result | Defect Ref | Notes |
|-------|------|--------|-----------|--------|-----------|-------|
| 1 | {{DATE}} | {{NAME}} | v{{X.Y.Z}} | Pass / Fail | D-{{NNN}} | — |
