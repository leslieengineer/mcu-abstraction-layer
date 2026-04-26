---
title: "State Machine Specifications"
type: readme
folder: State-Machines
---

# State Machines

> Formal state machine specifications for PX4 modules with complex behavior.
> Use template: [TEMPLATE-State-Machine.md](../../12-Templates/TEMPLATE-State-Machine.md)

## State Machine List

| Module | States | File | Status |
|--------|--------|------|--------|
| `commander` (Arming) | 5 states | `commander-arming-SM.md` | ✅ |
| `commander` (Main State) | 8 states | `commander-main-SM.md` | ✅ |
| `navigator` (Mission) | 6 states | `navigator-mission-SM.md` | ✅ |
| `land_detector` | 4 states | `land-detector-SM.md` | ✅ |
| `flight_mode_manager` | 12+ flight modes | `fmm-modes-SM.md` | ✅ |

## Commander Arming State Machine (Summary)

```
[INIT] → [STANDBY] → [ARMED] → [STANDBY]
           │                        │
           └── preflight checks     └── disarm command
           │                        │
           ▼                        ▼
     [ARM_DENIED]             [IN_AIR_RESTORE]
```

| State | Entry Condition | Exit Condition |
|-------|----------------|----------------|
| `INIT` | Power-on reset | Sensor init complete |
| `STANDBY` | All preflight checks pass | Arm command + safety switch off |
| `ARMED` | Arm command accepted | Disarm command OR auto-disarm timeout |
| `IN_AIR_RESTORE` | Reboot while flying | Attitude estimation restored |

## Documentation Standard

Each state machine document includes:
1. **State diagram** (text-based ASCII or Mermaid)
2. **State table**: State × Event → Action + Next State
3. **Guard conditions** (e.g., `preflight_check_passed && safety_off`)
4. **Entry/Exit actions**
5. **Error / timeout handling** (failsafe transitions)
