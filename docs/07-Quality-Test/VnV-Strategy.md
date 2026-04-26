---
title: "Verification & Validation Strategy"
type: document
doc-id: VNV
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# Verification & Validation Strategy

## 1. V&V Approach

| Level | Method | Tool | Coverage Target | Responsible |
|-------|--------|------|----------------|------------|
| Unit Test | Automated (host) | Google Test (gtest) + CMake CTest | 60%+ line coverage (critical modules) | Module developer |
| SITL | Automated (host) | PX4 SITL + Gazebo / jMAVSim | All flight modes + failsafes | QA / Dev |
| HITL | Semi-automated | PX4 HITL + Pixhawk HW + Gazebo | Sensor integration, timing | Integration Lead |
| System Test | Manual flight test | QGroundControl + test protocol | All PRD requirements | Test Pilot + QA |
| CI Regression | Automated | GitHub Actions | Build + unit + SITL smoke | CI pipeline |

## 2. Test Environment

| Environment | Hardware | Software | Purpose |
|------------|----------|----------|---------|
| Host (SITL) | x86 Linux (CI runners) | PX4 + NuttX POSIX sim + Gazebo | Unit tests, flight sim, fast iteration |
| HITL | Pixhawk v6X + USB + GCS PC | Real PX4 firmware, simulated dynamics | Timing, driver integration, MAVLink |
| Flight Test | Pixhawk v6X + frame + motors | Production firmware | Real-world flight validation |

## 3. Entry / Exit Criteria

### Test Entry
- [ ] Code compiles with zero warnings (`make px4_fmu-v6x` and `make px4_sitl`)
- [ ] `make tests` passes (unit tests on host)
- [ ] Static analysis clean (`cppcheck`, `clang-tidy`)
- [ ] Code review approved (GitHub PR)

### Test Exit
- [ ] All planned SITL test cases pass
- [ ] No open Critical or Major defects
- [ ] Flight mode transitions verified in SITL
- [ ] At least 1 HITL flight validates changed modules
- [ ] RC release notes updated

## 4. Defect Severity

| Severity | Description | Resolution SLA |
|----------|-------------|---------------|
| **Critical** | Crash to desktop (SITL), fly-away, loss of control | Must fix before RC tag |
| **Major** | Failsafe not triggered, EKF divergence, mode transition failure | Must fix before stable release |
| **Minor** | Logging gap, parameter description wrong, cosmetic GCS issue | Fix in next minor release |
| **Trivial** | Typo, code style, non-functional | Fix when convenient |

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
