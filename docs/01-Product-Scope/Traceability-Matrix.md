---
title: "Requirements Traceability Matrix"
type: document
doc-id: RTM
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# Requirements Traceability Matrix

> Maps every requirement from source → design → implementation → test.
> Ensures 100% bi-directional traceability.

## Matrix

| Req-ID | PRD Ref | SRS Ref | Design Ref | Module/File | Test Case | Test Result | Status |
|--------|---------|---------|------------|-------------|-----------|-------------|--------|
| RTM-001 | PRD-F-001 | SRS-F-001 | SDD-ARCH §2 | `mc_rate_control/` | TC-SITL-MC-Hover | Pass | ✅ |
| RTM-002 | PRD-F-002 | SRS-F-003 | SDD-ARCH §2 | `mc_pos_control/` | TC-SITL-MC-PosHold | Pass | ✅ |
| RTM-003 | PRD-F-003 | SRS-F-005 | Navigator module | `navigator/` | TC-SITL-MC-Mission | Pass | ✅ |
| RTM-004 | PRD-F-004 | SRS-F-006 | Commander failsafe | `commander/` | TC-SITL-RTL | Pass | ✅ |
| RTM-005 | PRD-F-005 | SRS-F-007 | Navigator geofence | `navigator/geofence.cpp` | TC-SITL-Geofence | Pass | ✅ |
| RTM-006 | PRD-F-006 | SRS-F-008 | EKF2 module | `ekf2/` | TC-EKF2-Replay | Pass | ✅ |
| RTM-007 | PRD-F-008 | SRS-F-011 | MAVLink module | `mavlink/` | TC-MAVLink-Bidir | Pass | ✅ |
| RTM-008 | PRD-F-010 | SRS-F-014 | DroneCAN module | `uavcan/` | TC-CAN-ESC | Pass | ✅ |
| RTM-009 | PRD-F-011 | SRS-F-016 | PWM output | `pwm_out/` | TC-PWM-Output | Pass | ✅ |
| RTM-010 | PRD-F-012 | SRS-F-018 | Control allocator | `control_allocator/` | TC-Alloc-Hex | Pass | ✅ |
| RTM-011 | PRD-F-013 | SRS-F-019 | Commander module | `commander/` | TC-Arming-Checks | Pass | ✅ |
| RTM-012 | PRD-F-014 | SRS-F-020 | Commander failsafe | `commander/failsafe/` | TC-Failsafe-Cascade | Pass | ✅ |
| RTM-013 | PRD-F-016 | SRS-F-023 | Logger module | `logger/` | TC-ULog-Recording | Pass | ✅ |
| RTM-014 | PRD-F-017 | SRS-F-024 | Param module | `param/` | TC-Param-SaveLoad | Pass | ✅ |
| RTM-015 | PRD-F-019 | SRS-F-026 | SITL platform | `platforms/posix/` | TC-SITL-Build | Pass | ✅ |

> **Status Legend**: 🔲 Not verified · 🔶 Partially verified · ✅ Fully verified · ❌ Failed

## Coverage Summary

| Metric | Count | Percentage |
|--------|-------|-----------|
| Total Requirements (SRS) | 51 | — |
| Traced in RTM (this table) | 15 | 29% |
| Traced to Design | 15 | 100% of traced |
| Traced to Test | 14 | 93% of traced |
| Verified (Pass) | 13 | 87% of traced |
| Remaining to trace | 36 | 71% |

> **Note**: This RTM covers the 15 highest-priority requirement chains.
> Full 51-requirement traceability is tracked in the project management tool.

## Rules

1. Every SRS requirement MUST have at least one test case
2. Every test case MUST trace back to at least one SRS requirement
3. Update this matrix whenever requirements, design, or tests change
4. Gap analysis: run before every major milestone review

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
