---
title: "ADR-0002: Use a layered GPIO abstraction with core API and chip-specific extensions"
type: adr
---

# ADR-0002: Use a layered GPIO abstraction with core API and chip-specific extensions

## Status

> Proposed | Accepted | Deprecated | Rejected

Proposed

## Date

2026-04-26

## Context

The project aims to support multiple microcontroller families, starting with ESP32 and STM32, behind a common GPIO abstraction layer. The application layer should not depend on vendor-specific GPIO APIs, but different chips still expose different capabilities and configuration models.

The abstraction therefore needs to balance three goals:

- provide a stable common API for the application layer
- allow chip-specific backend implementations
- avoid forcing unrelated features into a single monolithic interface

## Decision

Create a layered GPIO abstraction with:

- a small, stable core API for operations that are common across supported chips
- backend-specific implementations for ESP32, STM32, and future targets
- optional extension APIs for capabilities that are not universally shared

The core API should cover the most common GPIO operations only, such as init, deinit, direction control, read, write, pull configuration, and basic interrupt configuration.

Chip-specific features that do not map cleanly across targets should be exposed through extension interfaces or backend-specific APIs rather than being forced into the core contract.

Internally, each backend may use its own context object and function pointer table to implement the shared contract.

## Alternatives Considered

| Option | Pros | Cons |
|--------|------|------|
| Use vendor-specific GPIO APIs directly in application code | Simple for a single target | No portability, app becomes tied to a specific MCU family |
| Create one large GPIO interface that includes every feature from every chip | One entry point for the app | Bloated API, weak abstraction, hard to maintain, semantics differ across chips |
| **Use a layered core API with optional extensions** (selected) | Clear separation, portable core, extensible backends | Requires more design work up front and discipline around what belongs in the core |

## Consequences

### Positive
- The application layer can stay portable across MCU families.
- Backend-specific behavior remains isolated from the shared API.
- The core interface can remain stable even as new chips or features are added.
- Optional extensions make it possible to support special capabilities without polluting the common contract.

### Negative
- Some features will need separate extension APIs.
- More design and documentation effort is required than with direct vendor APIs.

### Risks
- The core API may grow too large if chip-specific features are not kept out of it.
- Contributors may introduce inconsistent semantics across backends if extension boundaries are not defined clearly.

## Related

- Supersedes: —
- Related requirements: —
- Related documents: [TEMPLATE-ADR.md](../../12-Templates/TEMPLATE-ADR.md)