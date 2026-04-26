---
title: "Decision Log"
type: log
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# Decision Log

> Non-architecture project decisions. For architecture decisions, use ADR in `02-System-Architecture/ADR/`.

## Log

| D-ID | Date | Decision | Context | Alternatives | Rationale | Decided By | Status |
|------|------|----------|---------|-------------|-----------|-----------|--------|
| D-001 | 2024-06-15 | Use GitHub Actions for CI | Need automated build + SITL on every PR | Jenkins, Buildkite, Drone CI | GitHub-native, free for open-source, matrix build support | Core Team | Active |
| D-002 | 2024-07-01 | Use Google Test for unit tests | Need host-side unit test framework compatible with CMake | Unity, CppUTest, Catch2 | C++ native, mature, CMake `FetchContent` integration, wide adoption | Core Team | Active |
| D-003 | 2024-08-10 | Adopt Kconfig for board config | `.px4board` files becoming unwieldy with 80+ boards | Flat CMake options, YAML config | Kconfig provides dependency resolution, menuconfig UI, proven in Linux kernel | Arch Lead | Active |
| D-004 | 2024-09-20 | QGroundControl as primary GCS | Need reference GCS for MAVLink testing | Mission Planner, APM Planner, custom | Native MAVLink 2.0, cross-platform Qt, maintained by Dronecode | PM | Active |
| D-005 | 2024-10-01 | Use BSON for parameter storage | Need compact persistent params on SD + flash | JSON, Protobuf, raw binary | 50% smaller than JSON, schema-less, already in PX4 codebase | Firmware Lead | Active |

## What Goes Here vs ADR

| This Log (Decision Log) | ADR |
|-------------------------|-----|
| Tool selection | Chip/component selection |
| Process/workflow changes | Protocol selection |
| Schedule decisions | Security architecture |
| Vendor selection | Memory layout |
| Team structure | SW architecture patterns |

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
