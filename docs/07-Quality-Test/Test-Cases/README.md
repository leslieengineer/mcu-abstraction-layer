---
title: "Test Cases"
type: readme
folder: Test-Cases
---

# Test Cases

> Individual test case files for PX4 v1.16.1 verification.
> Use template: [TEMPLATE-Test-Case.md](../../12-Templates/TEMPLATE-Test-Case.md)

## Test Case Register

| TC-ID | Title | SRS Ref | Level | Priority | Status |
|-------|-------|---------|-------|----------|--------|
| TC-001 | Attitude stabilization (hover, no wind) | SRS-F-001 | SITL | High | ✅ |
| TC-002 | EKF2 accel+gyro+baro fusion accuracy | SRS-F-008 | Unit + SITL | High | ✅ |
| TC-003 | GPS position hold within ±1.5 m | SRS-F-003 | SITL + Flight | High | ✅ |
| TC-004 | Mode transition Manual→Position→Mission→RTL | SRS-F-029 | SITL | High | ✅ |
| TC-005 | RC loss triggers RTL failsafe | SRS-F-006 | SITL | High | ✅ |
| TC-006 | GPS loss falls back to altitude mode | SRS-F-020 | SITL | High | ✅ |
| TC-007 | Battery low triggers RTL | SRS-F-021 | SITL | High | ✅ |
| TC-008 | Battery critical triggers Land | SRS-F-021 | SITL | High | ✅ |
| TC-009 | MAVLink heartbeat sent at 1 Hz | SRS-F-011 | Integration | Medium | ✅ |
| TC-010 | ULog logged at configured rate to SD | SRS-F-023 | HITL | Medium | 🔶 |
| TC-011 | DroneCAN ESC throttle command delivery | SRS-F-014 | HITL | Medium | 🔶 |
| TC-012 | Commander arming sequence (preflight checks) | SRS-F-019 | SITL | High | ✅ |
| TC-013 | Geofence breach triggers RTL | SRS-F-007 | SITL | Medium | ✅ |
| TC-014 | IMU redundancy: primary fail, switch to backup | SRS-F-010 | SITL | High | 🔲 |
| TC-015 | Control loop rate ≥250 Hz under load | SRS-NF-001 | HITL | High | ✅ |

## Naming Convention

```
TC-NNN-short-description.md
```

Example: `TC-001-hover-stabilization.md`
