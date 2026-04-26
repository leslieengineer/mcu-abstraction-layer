---
title: "TEMPLATE — Module Design"
type: template
template-for: Module-Design
---

# Module Design: {{MODULE_NAME}}

## 1. Purpose

> What does this module do? One paragraph.

## 2. Module Metadata

| Field | Value |
|-------|-------|
| Module Name | `{{module_name}}` |
| Source Files | `{{module_name}}.c`, `{{module_name}}.h` |
| Layer | Application / Service / HAL / Driver |
| Owner | {{NAME}} |
| Requirements | SRS-F-{{NNN}}, SRS-F-{{NNN}} |

## 3. Dependencies

### Uses (downstream)
| Module | API Called | Purpose |
|--------|-----------|---------|
| `{{dep_module}}` | `{{function()}}` | {{PURPOSE}} |

### Used By (upstream)
| Module | API Called | Purpose |
|--------|-----------|---------|
| `{{caller_module}}` | `{{function()}}` | {{PURPOSE}} |

## 4. Public API

```c
/**
 * @brief  Initialize the module
 * @pre    HAL layer initialized
 * @post   Module ready for operation
 * @return STATUS_OK on success
 */
status_t {{module}}_init(void);

/**
 * @brief  {{DESCRIPTION}}
 * @param  {{PARAM}} — {{DESCRIPTION}}
 * @return STATUS_OK on success
 */
status_t {{module}}_{{action}}({{params}});
```

## 5. Internal Design

### Data Flow

```
[Input] ──▶ [Process] ──▶ [Output]
```

### Key Data Structures

```c
typedef struct {
    {{type}} {{field}};  /**< {{description}} */
} {{module}}_data_t;
```

## 6. State Machine

> If this module has a state machine, reference:
> `05-Firmware-Design/State-Machines/{{MODULE_NAME}}-SM.md`

## 7. Configuration

| Parameter | Type | Default | Range | Description |
|-----------|------|---------|-------|-------------|
| `{{PARAM}}` | {{TYPE}} | {{DEFAULT}} | {{RANGE}} | {{DESCRIPTION}} |

## 8. Error Handling

| Error | Cause | Module Action | Caller Gets |
|-------|-------|--------------|-------------|
| {{ERROR}} | {{CAUSE}} | {{ACTION}} | `STATUS_ERR_{{TYPE}}` |

## 9. Resource Usage

| Resource | Estimate |
|----------|----------|
| Code size (flash) | ~{{N}} KB |
| RAM (static) | ~{{N}} B |
| RAM (stack) | ~{{N}} B |
| CPU (worst case) | ~{{N}} µs per call |
