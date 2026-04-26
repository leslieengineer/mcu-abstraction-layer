---
title: "Glossary"
type: document
doc-id: PM-GLO
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# Glossary

> Project-specific terminology. Alphabetical order.
> Include domain terms, abbreviations, and acronyms used in this project.

## Terms

| Term | Abbreviation | Definition | Context |
|------|-------------|-----------|--------|
| Architecture Decision Record | ADR | A document capturing a significant design decision and its rationale | Used in `02-System-Architecture/ADR/` |
| Bill of Materials | BOM | Complete list of components needed to build the product | `03-Hardware/BOM-Management.md` |
| Controller Area Network | CAN | Serial bus standard for real-time distributed control | DroneCAN ESC/GPS bus |
| Design by Contract | DbC | Programming methodology using preconditions, postconditions, invariants | `05-Firmware-Design/Coding-Standard.md` |
| DroneCAN | — | CAN bus protocol for UAV peripherals (formerly UAVCAN v0) | ESC, GPS, airspeed sensors |
| Extended Kalman Filter | EKF2 | 24-state sensor fusion algorithm for position/velocity/attitude estimation | `src/modules/ekf2/` |
| Ground Control Station | GCS | Software for UAV mission planning and monitoring (e.g., QGroundControl) | MAVLink interface |
| Hardware Abstraction Layer | HAL | Software layer abstracting MCU peripheral registers | `05-Firmware-Design/Driver-HAL-Layer.md` |
| Hardware-In-The-Loop | HITL | Testing with real autopilot hardware connected to simulator | `07-Quality-Test/VnV-Strategy.md` |
| Interface Control Document | ICD | Formal contract defining interface between two systems | `06-Communication-Protocol/` |
| Micro Air Vehicle Link | MAVLink | Lightweight messaging protocol for UAV-to-GCS communication (v2.0) | `06-Communication-Protocol/` |
| Non-Volatile Storage | NVS | Flash-based key-value store for persistent configuration | `05-Firmware-Design/Memory-Partition.md` |
| NuttX | — | Real-Time Operating System (RTOS) used by PX4, POSIX-compliant | `src/platforms/nuttx/` |
| Over-The-Air | OTA | Remote firmware update mechanism | — |
| Root Cause Analysis | RCA | Systematic process to identify the fundamental cause of a defect | `07-Quality-Test/Defect-Taxonomy-RCA.md` |
| Software-In-The-Loop | SITL | Full PX4 firmware compiled for host PC with physics simulator | CI pipeline, development |
| uORB | — | Micro Object Request Broker — PX4's internal publish-subscribe IPC | All inter-module communication |
| Verification & Validation | V&V | Ensuring product is built right (verification) and is the right product (validation) | `07-Quality-Test/VnV-Strategy.md` |

## Project-Specific Terms

| Term | Definition |
|------|----------|
| `.px4` firmware package | Archive containing compiled `.bin` + JSON metadata, uploaded by bootloader |
| `.px4board` | Kconfig-based board configuration file defining enabled modules/drivers per board |
| Control Allocator | Module mapping virtual torque/thrust commands to individual actuator outputs |
| Flight Mode Manager | State machine managing transitions between flight modes (Manual, Position, Mission, RTL) |
| Mixer | Legacy actuator mapping system (replaced by Control Allocator in v1.14+) |
| ROMFS | Read-only filesystem baked into firmware image containing startup scripts and airframe configs |
| Work Queue | NuttX kernel-scheduled thread pool used by PX4 drivers and modules |

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
