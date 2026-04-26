---
title: "TEMPLATE — State Machine"
type: template
template-for: State-Machine
---

# State Machine: {{MODULE_NAME}}

## 1. Overview

| Field | Value |
|-------|-------|
| Module | `{{module_name}}` |
| States | {{N}} |
| Events | {{N}} |
| Initial State | `{{STATE_INIT}}` |

## 2. State Diagram

```
        ┌──────────────┐
   ┌───▶│  STATE_INIT  │
   │    └──────┬───────┘
   │           │ event_A
   │           ▼
   │    ┌──────────────┐
   │    │  STATE_ACTIVE │──── event_C ────▶ ┌──────────────┐
   │    └──────┬───────┘                    │  STATE_ERROR │
   │           │ event_B                    └──────┬───────┘
   │           ▼                                   │ event_D
   │    ┌──────────────┐                           │
   │    │  STATE_DONE  │◀──────────────────────────┘
   │    └──────┬───────┘
   │           │ event_E
   └───────────┘
```

> Replace with `.drawio` or `.puml` diagram for complex state machines.

## 3. State Table

| Current State | Event | Guard | Action | Next State |
|--------------|-------|-------|--------|-----------|
| `STATE_INIT` | `event_A` | — | `action_init()` | `STATE_ACTIVE` |
| `STATE_ACTIVE` | `event_B` | `guard_done()` | `action_complete()` | `STATE_DONE` |
| `STATE_ACTIVE` | `event_C` | `guard_error()` | `action_error()` | `STATE_ERROR` |
| `STATE_ERROR` | `event_D` | — | `action_recover()` | `STATE_DONE` |
| `STATE_DONE` | `event_E` | — | `action_reset()` | `STATE_INIT` |
| `*` (any) | `event_timeout` | `timeout > {{N}}ms` | `action_timeout()` | `STATE_ERROR` |

## 4. State Descriptions

| State | Description | Entry Action | Exit Action |
|-------|-------------|-------------|-------------|
| `STATE_INIT` | {{DESCRIPTION}} | {{ACTION}} | {{ACTION}} |
| `STATE_ACTIVE` | {{DESCRIPTION}} | {{ACTION}} | {{ACTION}} |
| `STATE_ERROR` | {{DESCRIPTION}} | {{ACTION}} | {{ACTION}} |
| `STATE_DONE` | {{DESCRIPTION}} | {{ACTION}} | {{ACTION}} |

## 5. Guard Conditions

| Guard | Condition | Description |
|-------|-----------|-------------|
| `guard_done()` | `count >= target` | Processing complete |
| `guard_error()` | `error_flag == true` | Error detected |

## 6. Timeout / Watchdog

| State | Max Duration | Timeout Action |
|-------|-------------|---------------|
| `STATE_ACTIVE` | {{N}} ms | Transition to `STATE_ERROR` |
