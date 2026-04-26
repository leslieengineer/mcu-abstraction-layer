---
title: "Compliance Matrix"
type: document
doc-id: CMP
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# Compliance Matrix

> Maps applicable standards to evidence of compliance for PX4 Autopilot.

## 1. Applicable Standards

| Standard | Version | Scope | Mandatory / Voluntary |
|----------|---------|-------|----------------------|
| DO-178C | 2011 | Software for airborne systems | Voluntary (reference for design rigor) |
| DO-254 | 2000 | Airborne electronic hardware | Voluntary (reference for Pixhawk HW) |
| MIL-STD-810G | 2008 | Environmental test methods | Voluntary (vibration, temp, altitude) |
| MAVLink Protocol | v2.0 | GCS communication | Mandatory (interop with QGC) |
| DroneCAN (UAVCAN v0) | 2020 | CAN bus peripherals | Mandatory (ESC, GPS modules) |
| IEC 61508 | 2010 | Functional safety of E/E/PE systems | Voluntary (SIL 2 target for flight-critical) |
| ISO 21384-3 | 2021 | UAS — Operation procedures | Voluntary (operational safety) |
| EU 2019/947 (EASA) | 2019 | UAS operational regulation | Mandatory (EU operations) |
| FAA Part 107 | 2016 | Small UAS operations | Mandatory (US operations) |

## 2. Compliance Mapping

| Standard | Clause | Requirement Summary | Evidence | Status |
|----------|--------|-------------------|----------|--------|
| DO-178C | §6.3 | Traceability: requirements → code → tests | [Traceability-Matrix.md](../01-Product-Scope/Traceability-Matrix.md) | 🔶 |
| DO-178C | §6.4 | Code review process | GitHub PR reviews + CI checks | ✅ |
| DO-178C | §6.7 | Test coverage analysis | `make tests` + SITL coverage reports | 🔶 |
| MAVLink v2.0 | §2 | Message framing, CRC, sequence | `mavlink` module compliance | ✅ |
| MAVLink v2.0 | §3 | Heartbeat + system status | `commander` publishes `HEARTBEAT` at 1 Hz | ✅ |
| DroneCAN | §4.2 | Node status broadcast (1 Hz) | `uavcan` module implements `NodeStatus` | ✅ |
| DroneCAN | §5.1 | ESC raw command interface | `uavcan` → `esc.RawCommand` at control rate | ✅ |
| MIL-STD-810G | 514.7 | Vibration (random, sinusoidal) | Pixhawk v6X vibration test report | ✅ |
| EU 2019/947 | Art. 4 | Geofence capability | `navigator` geofence module | ✅ |
| IEC 61508 | Part 3 §7.4.4 | Coding standard + static analysis | MISRA subset + `cppcheck` + CI gates | 🔶 |

## 3. Gap Analysis

| Standard | Clause | Gap Description | Remediation Plan | Target Date |
|----------|--------|----------------|-----------------|-------------|
| DO-178C | §6.3 | Full code-level traceability not maintained | Implement traceability tooling (e.g., Sphinx + tags) | 2025-Q4 |
| DO-178C | §6.7 | MCDC coverage not measured | Add gcov/lcov to CI for critical modules | 2025-Q4 |
| ISO 21384-3 | §5 | No formal operational manual | Create flight operations SOP document | 2025-Q2 |
| IEC 61508 | Part 3 §7.4.4 | MISRA C:2012 subset not formally adopted | Define and enforce MISRA subset via CI (see Coding-Standard.md Appendix A) | 2025-Q4 |

## 4. Audit Readiness

- [x] All protocol standards mapped (MAVLink, DroneCAN)
- [x] All environmental test standards mapped
- [ ] DO-178C full traceability gap closed
- [ ] MCDC coverage tooling integrated
- [x] Document register reflects current versions

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
