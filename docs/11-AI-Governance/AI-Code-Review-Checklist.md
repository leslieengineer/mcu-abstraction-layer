---
title: "AI Code Review Checklist"
type: document
doc-id: AI-CHK
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# AI Code Review Checklist

> Use this checklist when reviewing any AI-generated code before merge into PX4.

## Review Checklist

### Correctness
- [ ] Logic matches the requirement (SRS-F-xxx ref verified)
- [ ] Edge cases handled (boundary values, empty input, max values)
- [ ] No off-by-one errors in loops/arrays
- [ ] Correct endianness for multi-byte MAVLink / DroneCAN fields
- [ ] Correct signedness (signed/unsigned) for arithmetic
- [ ] uORB message fields match `.msg` definition types

### Memory Safety
- [ ] No buffer overflows (all array accesses bounds-checked)
- [ ] No use-after-free or dangling pointers
- [ ] Stack usage within budget (check with NuttX `top` watermarks; typical limit 1.5–6 KB per task)
- [ ] No dynamic allocation after init (`new`/`malloc` only in constructors)
- [ ] No unbounded recursion

### Concurrency (NuttX RTOS)
- [ ] Shared resources protected by mutex / `LockGuard` / critical section
- [ ] No priority inversion risk (use NuttX priority inheritance mutexes)
- [ ] ISR is minimal (set flag / `work_queue` post only, no blocking calls)
- [ ] No deadlock possibility (consistent lock ordering)
- [ ] uORB publish/subscribe is thread-safe (no manual locking needed)

### Hardware Interaction
- [ ] Register writes match datasheet specification
- [ ] Correct SPI/I2C bus and chip-select per board pinout
- [ ] Required power-on delays after sensor configuration changes
- [ ] Pin configuration matches schematic (check `board_config.h`)

### PX4 Coding Standard
- [ ] Naming convention followed (PascalCase classes, `_snake_case` members)
- [ ] No compiler warnings with `-Werror`
- [ ] `PX4_ERR/WARN/INFO` used for logging (not `printf`)
- [ ] `DEFINE_PARAMETERS` macro used for tunable params
- [ ] `ModuleBase` / `I2CSPIDriver` patterns used correctly
- [ ] No forbidden practices (see `05-Firmware-Design/Coding-Standard.md`)

### Security
- [ ] No hardcoded secrets or MAVLink signing keys
- [ ] Input validation at MAVLink message boundaries
- [ ] No information leakage in `STATUSTEXT` error messages

### Architecture
- [ ] Module communicates only via uORB (no global variables across modules)
- [ ] New uORB topic has corresponding `.msg` file
- [ ] Work queue scheduling used (no bare `while(true)` loops)
- [ ] No circular module dependencies

## Verdict

| Verdict | Action |
|---------|--------|
| **Approved** | Merge allowed |
| **Approved with comments** | Minor fixes, re-review not needed |
| **Changes requested** | Must fix and re-review |
| **Rejected** | Major safety/architecture issues, rewrite required |

Reviewer: _______________
Date: _______________
Verdict: _______________

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
