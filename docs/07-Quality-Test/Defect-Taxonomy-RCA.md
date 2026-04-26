---
title: "Defect Taxonomy & Root Cause Analysis"
type: document
doc-id: QA-RCA
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# Defect Taxonomy & Root Cause Analysis

## 1. Defect Categories

| Category | Code | Description | PX4 Example |
|----------|------|-------------|-------------|
| Requirements | REQ | Missing, ambiguous, or wrong requirement | Undefined behavior when GPS + baro both fail |
| Design | DES | Architecture or design flaw | uORB topic rate mismatch between publisher/subscriber |
| Code | COD | Implementation bug | Off-by-one in EKF2 covariance reset |
| Integration | INT | Interface mismatch | MAVLink message version incompatibility with QGC |
| Configuration | CFG | Build, config, or parameter issue | Wrong `SYS_AUTOSTART` airframe ID |
| Hardware | HW | PCB or component issue | IMU vibration coupling on Pixhawk v5X baseplate |
| Driver | DRV | Sensor driver bug | ICM42688P FIFO overflow not handled |
| Test | TST | Test setup or procedure error | SITL sim clock drift causing false timeout |

## 2. Defect Log

| ID | Date | Category | Severity | Summary | Module | Root Cause | Status |
|----|------|----------|----------|---------|--------|-----------|--------|
| D-001 | 2025-01-05 | DRV | Major | BMI088 gyro spikes at startup | `bmi088` | Missing 80 ms power-on delay before first read | Fixed |
| D-002 | 2025-01-12 | DES | Critical | EKF2 diverges on GPS glitch | `ekf2` | Innovation gate too wide for position sudden jump | Fixed |
| D-003 | 2025-01-20 | INT | Major | QGC shows wrong battery % | `mavlink` | `BATTERY_STATUS` cell_count field not populated | Fixed |
| D-004 | 2025-02-01 | CFG | Minor | Logger starts before SD mounted | `logger` | Startup script order race condition | Fixed |

## 3. Root Cause Analysis (5-Why Template)

### D-002: EKF2 diverges on GPS glitch

| Why # | Question | Answer |
|-------|----------|--------|
| 1 | Why did EKF2 diverge? | Position innovation exceeded 100 m in one step |
| 2 | Why was innovation so large? | GPS reported a 150 m position jump |
| 3 | Why wasn't the GPS jump rejected? | Innovation gate was set to 5σ which allowed it |
| 4 | Why was the gate so wide? | Default `EKF2_GPS_P_GATE` tuned for RTK, not consumer GPS |
| 5 | Why? (root cause) | **No separate gate parameter for consumer vs RTK GPS receivers** |

**Corrective Action**: Tighten default `EKF2_GPS_P_GATE` to 3.0; add GPS quality pre-check.
**Preventive Action**: Add SITL test case that injects GPS position jumps.

## 4. Defect Metrics Dashboard

| Metric | Value | Target |
|--------|-------|--------|
| Total Defects (v1.16 cycle) | 47 | — |
| Open Critical | 0 | 0 at release |
| Open Major | 2 | 0 at release |
| Defect Density (per KLOC) | 0.12 | < 0.5 |
| Avg Time to Fix (days) | 8 | < 14 |

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
