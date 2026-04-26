---
title: "Module Design Documents"
type: readme
folder: Module-Design
---

# Module Design

> Each PX4 firmware module gets its own design document.
> Use template: [TEMPLATE-Module-Design.md](../../12-Templates/TEMPLATE-Module-Design.md)

## Module List

| Module | Source Path | Owner | Work Queue | Status |
|--------|-----------|-------|-----------|--------|
| `commander` | `src/modules/commander/` | PX4 Core | `wq:hp_default` | ✅ |
| `ekf2` | `src/modules/ekf2/` | PX4 Core | `wq:nav_and_controllers` | ✅ |
| `mc_rate_control` | `src/modules/mc_rate_control/` | PX4 Core | `wq:rate_ctrl` | ✅ |
| `mc_pos_control` | `src/modules/mc_pos_control/` | PX4 Core | `wq:nav_and_controllers` | ✅ |
| `navigator` | `src/modules/navigator/` | PX4 Core | `wq:nav_and_controllers` | ✅ |
| `control_allocator` | `src/modules/control_allocator/` | PX4 Core | `wq:hp_default` | ✅ |
| `mavlink` | `src/modules/mavlink/` | PX4 Core | `wq:lp_default` | ✅ |
| `logger` | `src/modules/logger/` | PX4 Core | `wq:lp_default` | ✅ |
| `land_detector` | `src/modules/land_detector/` | PX4 Core | `wq:hp_default` | ✅ |
| `flight_mode_manager` | `src/modules/flight_mode_manager/` | PX4 Core | `wq:nav_and_controllers` | ✅ |
| `battery_status` | `src/modules/battery_status/` | PX4 Core | `wq:lp_default` | ✅ |
| `sensors` | `src/modules/sensors/` | PX4 Core | `wq:INS0` | ✅ |
| `manual_control` | `src/modules/manual_control/` | PX4 Core | `wq:hp_default` | ✅ |

## What Goes in a Module Design Doc

1. **Purpose** — What this module does
2. **API** — uORB subscriptions (inputs) and publications (outputs)
3. **Dependencies** — Which uORB topics it subscribes to / publishes
4. **State Machine** — If applicable (link to `State-Machines/`)
5. **Data Flow** — Input topics → processing → output topics
6. **Configuration** — `DEFINE_PARAMETERS` param list
7. **Error Handling** — Failsafe triggers, degraded modes
8. **Resource Usage** — Stack size, CPU time per `Run()` call
