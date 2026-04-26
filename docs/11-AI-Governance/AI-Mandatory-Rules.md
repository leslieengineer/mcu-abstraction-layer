---
title: "AI Agent Mandatory Rules"
type: document
doc-id: AI-MAN
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# AI Agent Mandatory Rules

> These rules MUST be followed by any AI agent working on the PX4 project.
> Violations require immediate correction before merge.

## Hard Constraints

### 1. Code Safety (Flight-Critical)

- **NEVER** generate code that writes to hardware registers without explicit comment explaining the register and expected effect
- **NEVER** disable watchdog (`IWDG`), arming checks, or failsafe logic without ADR approval
- **NEVER** use `malloc` / `free` after system init phase — PX4 modules use static `ModuleBase` allocation
- **NEVER** use floating-point in ISR context (NuttX ISR is integer-only)
- **ALWAYS** validate buffer sizes before write operations
- **NEVER** modify commander arming state machine transitions without safety review
- **NEVER** bypass EKF2 innovation checks or sensor validity flags

### 2. Code Quality

- **ALWAYS** follow the PX4 coding standard (`05-Firmware-Design/Coding-Standard.md`)
- **ALWAYS** use `PX4_ERR/WARN/INFO/DEBUG` macros — never `printf` directly
- **ALWAYS** use `DEFINE_PARAMETERS` macro for tunable parameters (never hardcode tuning values)
- **NEVER** suppress compiler warnings (`#pragma warning(disable:...)`)
- **NEVER** use `goto` statements
- **ALWAYS** return PX4 error codes (`PX4_OK`, `PX4_ERROR`); never silently ignore errors
- **ALWAYS** schedule work via work queue — never bare `while(true)` loops in modules

### 3. Architecture

- **NEVER** create circular dependencies between modules
- **NEVER** access hardware registers directly from application/module layer (must go through NuttX HAL or PX4 driver class)
- **ALWAYS** communicate between modules via uORB publish/subscribe — never global variables or direct function calls
- **ALWAYS** respect the layered architecture in `05-Firmware-Design/Firmware-Architecture.md`
- **NEVER** add a new uORB topic without defining the `.msg` file in `msg/` directory

### 4. Documentation

- **ALWAYS** reference requirements (SRS-F-xxx) in code comments when implementing a feature
- **ALWAYS** update `CHANGELOG.md` when modifying controlled documents
- **NEVER** modify `Official-Document-Register.md` without human approval
- **ALWAYS** add `@author` and `@brief` doxygen comments on new modules

### 5. Security

- **NEVER** hardcode passwords, keys, or MAVLink signing keys in source
- **NEVER** disable MAVLink 2.0 message signing features without ADR approval
- **NEVER** generate code with known vulnerability patterns (buffer overflow, format string, etc.)
- **ALWAYS** use constant-time comparison for MAVLink signing verification

## Machine-Readable Summary

```yaml
ai-rules:
  safety:
    - no-direct-hw-register-without-comment
    - no-disable-watchdog-without-adr
    - no-dynamic-alloc-after-init
    - no-float-in-isr
    - validate-buffer-before-write
    - no-modify-arming-sm-without-review
    - no-bypass-ekf2-checks
  quality:
    - follow-px4-coding-standard
    - use-px4-log-macros
    - use-define-parameters-macro
    - no-suppress-warnings
    - no-goto
    - return-px4-error-codes
    - use-work-queue-scheduling
  architecture:
    - no-circular-deps
    - no-direct-hw-from-module-layer
    - uorb-only-ipc
    - respect-layers
    - msg-file-for-new-topics
  security:
    - no-hardcoded-secrets
    - no-disable-mavlink-signing-without-adr
    - no-known-vulnerabilities
    - constant-time-compare
```

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
