---
title: "Field Issue Investigation Playbook"
type: document
doc-id: OPS-FIP
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# Field Issue Investigation Playbook

> Step-by-step runbooks for diagnosing and resolving PX4 field issues.

## 1. General Investigation Procedure

```
[Issue Reported]
    │
    ▼
[1. Gather Info]  ← PX4 version (`ver all`), board HW rev, ULog file, flight conditions
    │
    ▼
[2. Categorize]   ← Sensor / EKF / Actuator / Power / Config / Pilot error
    │
    ▼
[3. Reproduce]    ← Can we reproduce in SITL or HITL?
    │
    ├── Yes ──▶ [4a. Debug & Fix] ──▶ [5. Verify Fix] ──▶ [6. Release Patch]
    │
    └── No  ──▶ [4b. Request ULog + params] ──▶ [Analyze in Flight Review] ──▶ [Wait]
```

## 2. Playbook: EKF2 Position Drift / Flyaway

### Symptom
> Vehicle drifts from position hold or moves unexpectedly in GPS mode.

### Possible Causes

| # | Cause | Likelihood | How to Verify |
|---|-------|-----------|--------------|
| 1 | GPS multipath / poor HDOP | High | Check `vehicle_gps_position.hdop` in ULog; verify antenna placement |
| 2 | Magnetometer interference | High | Check `ekf2 status` for mag innovation; compass calibration |
| 3 | IMU vibration clipping | Medium | Check `sensor_accel` FFT for clipping; vibration isolation mount |
| 4 | EKF2 parameter misconfiguration | Medium | Compare `EKF2_*` params with defaults |

### Investigation Steps

1. Download ULog from SD card or QGC
2. Upload to [Flight Review](https://review.px4.io) — check EKF2 innovations, GPS quality, vibration
3. Run `ekf2 status` on NSH console for real-time innovation checks
4. Check `sensor_status` for any failed/degraded sensors
5. Review `param show EKF2_*` for non-default values

### Resolution

| Root Cause | Fix | Firmware Change | Deployed In |
|-----------|-----|----------------|-------------|
| GPS multipath | Relocate GPS antenna, add ground plane | No | Config fix |
| Mag interference | Recalibrate compass, rotate mag mounting | No | Config fix |
| IMU vibration | Add damping mount, tighten `EKF2_ACC_NOISE` | Param only | Config fix |
| EKF2 gate too wide | Tighten `EKF2_GPS_P_GATE` to 3.0 | Yes | v1.16.1 |

---

## 3. Common Issue Templates

### 3.1 Vehicle Not Arming

**Check order**:
1. Pre-arm check messages in QGC: `commander status` on NSH
2. Sensor calibration: `sensor_status` — all sensors healthy?
3. RC calibration: `listener rc_channels` — valid stick inputs?
4. Safety switch: `listener safety` — button pressed?
5. Battery level: `listener battery_status` — above minimum?
6. GPS lock: `listener vehicle_gps_position` — 3D fix with HDOP < 2.0?
7. Geofence: flight plan within allowed area?

### 3.2 Unexpected Reboot in Flight

**Check order**:
1. `hardfault_log status` — check for stored crash dump
2. `dmesg` after reboot — NuttX boot reason
3. Power supply: check battery voltage in ULog at time of reset
4. Stack overflow: check `top` watermarks for low-stack tasks
5. Brownout: check `ver hwcmp` for reset cause (BOR flag)
6. Watchdog: if IWDG triggered, check which module stopped feeding

### 3.3 Motor / ESC Not Responding

**Check order**:
1. Actuator output: `listener actuator_outputs` — PWM values correct?
2. ESC calibration: PWM range (1000-2000 μs) matches ESC config?
3. DroneCAN ESC: `listener esc_status` — CAN bus connected?
4. Safety switch disarmed? Check safety uORB topic
5. Motor assignment: `param show MOT_ORDERING` + Control Allocator config
6. Hardware revision compatibility

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
