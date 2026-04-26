---
title: "Test Plan"
type: document
doc-id: STP
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# Software Test Plan (STP)

## 1. Scope

| Field | Value |
|-------|-------|
| System Under Test | PX4 Autopilot v1.16.1 (Pixhawk FMU-v6X) |
| Firmware Version | v1.16.1-rc1 |
| Test Period | 2024-12-01 → 2025-02-28 |
| Test Lead | PX4 QA Team |

## 2. Test Items

| Item | Version | Type | Notes |
|------|---------|------|-------|
| `ekf2` | v1.16 | Unit + SITL | State estimator: attitude, position, velocity |
| `mc_rate_control` | v1.16 | Unit + SITL | Rate PID controller |
| `mc_pos_control` | v1.16 | SITL + Flight | Position hold, mission tracking |
| `commander` | v1.16 | Unit + SITL | Arming, mode transitions, failsafes |
| `control_allocator` | v1.16 | Unit | Motor mixing, geometry-based allocation |
| `mavlink` | v1.16 | Integration | Message parsing, stream rates |
| `navigator` | v1.16 | SITL + Flight | Mission execution, RTL, geofence |
| Sensor drivers | v1.16 | HITL | ICM42688P, BMI088, BMP388, IST8310 |

## 3. Features to Test

| Feature | SRS Ref | Test Level | Priority |
|---------|---------|-----------|----------|
| Multicopter stabilization | SRS-F-001 | SITL + Flight | High |
| EKF2 sensor fusion (accel+gyro+mag+baro+GPS) | SRS-F-008 | SITL | High |
| Position hold accuracy (±1.5 m GPS mode) | SRS-F-003 | SITL + Flight | High |
| Mode transitions (Manual→Altitude→Position→Mission→RTL) | SRS-F-029 | SITL | High |
| Failsafe: RC loss → RTL | SRS-F-006 | SITL | High |
| Failsafe: GPS loss → altitude mode | SRS-F-020 | SITL | High |
| MAVLink telemetry to QGC | SRS-F-011 | Integration | Medium |
| ULog flight logging to SD | SRS-F-023 | HITL | Medium |
| DroneCAN ESC control | SRS-F-014 | HITL | Medium |
| Battery failsafe (RTL at low, Land at critical) | SRS-F-021 | SITL | High |

## 4. Features NOT to Test

| Feature | Reason |
|---------|--------|
| Fixed-wing flight | Not applicable to v6X multicopter baseline |
| VTOL transitions | Separate test campaign for VTOL builds |
| Cyphal (UAVCAN v1) | Experimental in v1.16, not production |

## 5. Test Schedule

| Phase | Start | End | Milestone |
|-------|-------|-----|-----------|
| Unit Testing | 2024-12-01 | 2024-12-15 | All `make tests` green |
| SITL Integration | 2024-12-15 | 2025-01-15 | All flight modes pass in Gazebo |
| HITL Testing | 2025-01-15 | 2025-02-01 | Sensor + motor integration verified |
| Flight Testing | 2025-02-01 | 2025-02-15 | Hover + mission + failsafe flights |
| Regression | 2025-02-15 | 2025-02-28 | No regressions from v1.15 |

## 6. Resource Requirements

| Resource | Quantity | Notes |
|----------|---------|-------|
| Pixhawk v6X boards | 2 | Rev v6X (production silicon) |
| Quadcopter test frame | 1 | 500-class, known PID tune |
| CI runners (Linux x86) | 4 | GitHub Actions self-hosted |
| Gazebo workstation | 1 | GPU-capable for SITL sim |
| Personnel | 3 | 1 dev, 1 QA, 1 test pilot |

## 7. Risk & Contingency

| Risk | Impact | Mitigation |
|------|--------|-----------|
| Board shortage | HITL/flight test delay | Pre-order 2 boards; SITL covers most cases |
| Weather (outdoor flight) | Flight test delay | Use indoor cage for basic hover tests |
| Gazebo version incompatibility | SITL failures | Pin Gazebo version in CI docker image |
| EKF2 regression | Wrong position estimates | Compare ULog against v1.15 baseline |

## 8. References

| Ref | Document | Version |
|-----|----------|--------|
| [1] | DO-178C — Software Considerations in Airborne Systems | 2011 |
| [2] | IEEE 1012 — Standard for System, Software, and Hardware V&V | 2016 |
| [3] | IEEE 829 — Standard for Test Documentation | 2008 |
| [4] | PX4 SITL Testing Guide (docs.px4.io/main/en/test_and_ci/) | v1.16 |
| [5] | Product-Requirements.md (SRS) | 1.0 |
| [6] | Requirements-Baseline.md | 1.0 |

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
