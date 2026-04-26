---
title: "Project Charter"
type: document
doc-id: CHARTER
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# Project Charter

## 1. Project Overview

| Field | Value |
|-------|-------|
| Project Name | PX4 Autopilot |
| Project Code | PX4 |
| Sponsor | Dronecode Foundation / Linux Foundation |
| Project Manager | Community-driven (core maintainers team) |
| Start Date | 2011 (ETH Zürich PIXHAWK project) |
| Target Completion | Continuous development (open-source) |

## 2. Purpose & Business Justification

PX4 Autopilot is an open-source flight control software for drones and other unmanned vehicles. It provides a complete autopilot solution that runs on dedicated flight controller hardware (Pixhawk family), providing autonomous flight, manual control, and mission planning capabilities. PX4 solves the problem of each drone manufacturer building proprietary flight stacks from scratch, by offering a robust, well-tested, open-source alternative that supports multicopters, fixed-wing aircraft, VTOL, rovers, and submarines.

## 3. Scope

### 3.1 In Scope

- [x] Flight controller firmware for NuttX RTOS
- [x] Support for multicopter (MC), fixed-wing (FW), VTOL, rover, submarine vehicle types
- [x] Sensor fusion (EKF2) for navigation and attitude estimation
- [x] MAVLink 2.0 communication with GCS (QGroundControl)
- [x] Autonomous mission execution (waypoint navigation, RTL, geofence)
- [x] Multi-platform: NuttX (hardware), POSIX (SITL simulation), QURT (Snapdragon)
- [x] 80+ board configurations (Pixhawk v2 through v6X, CUAV, Holybro, etc.)
- [x] DroneCAN/Cyphal peripheral support
- [x] ROS2 integration via XRCE-DDS bridge

### 3.2 Out of Scope

- Ground Control Station software (QGroundControl is a separate project)
- Hardware PCB design (Pixhawk standards are separate open-hardware projects)
- Payload-specific applications (camera, spray, delivery)

## 4. Stakeholders

| Name | Role | Responsibility | Contact |
|------|------|---------------|---------|
| Dronecode Foundation | Sponsor | Governance, funding, legal | dronecode.org |
| Lorenz Meier | Founder / Architect | Original creator, architecture oversight | ETH Zürich |
| PX4 Core Team | Maintainers | Code review, release management | GitHub PX4 org |
| Vehicle manufacturers | Integrators | Board support, custom configuration | Various |
| Drone operators | End users | Flight operations, mission planning | Community |
| Certification bodies | Regulators | DO-178C / EASA compliance | Aviation authorities |

## 5. Key Milestones

| Milestone | Target Date | Deliverable |
|-----------|------------|-------------|
| M1 — v1.16.0-alpha | 2024-Q3 | Feature-complete alpha build |
| M2 — v1.16.0-beta | 2024-Q4 | Beta with SITL/HITL validation |
| M3 — v1.16.0-rc1 | 2024-11 | Release candidate, regression testing |
| M4 — v1.16.1 | 2024-12 | Stable release |
| M5 — v1.17.0-alpha | 2025-Q1 | Next development cycle starts |

## 6. Success Criteria

1. All SITL test suites pass on supported vehicle types (MC, FW, VTOL)
2. No regression in EKF2 estimation accuracy (validated via flight replay)
3. Stable flight on all Tier-1 boards (Pixhawk v5X, v6X, v6C)
4. MAVLink GCS compatibility with QGroundControl latest release

## 7. Constraints & Assumptions

### Constraints
- Must maintain backward compatibility with MAVLink 2.0 message set
- NuttX RTOS required for all hardware targets (real-time guarantees)
- Memory budget: firmware binary < 2 MB Flash, ≤ 384 KB RAM on STM32H7
- BSD-3-Clause license — no GPL dependencies in core firmware

### Assumptions
- Hardware meets Pixhawk standard (FMUv5+) for sensor quality
- Pilots have basic training before flying with PX4
- Ground station (QGC) handles user-facing mission planning

## 8. Risks (High-Level)

> Detailed risks tracked in [Risk Register](../09-Project-Management/Risk-Register.md)

| Risk | Impact | Likelihood |
|------|--------|-----------|
| EKF divergence causing fly-away | High | Medium |
| Motor/ESC failure mid-flight | High | Low |
| GPS denial/jamming in urban areas | Medium | Medium |
| NuttX upstream breaking change | Medium | Low |

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
