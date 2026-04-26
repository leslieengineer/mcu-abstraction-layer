---
title: "Coding Standard"
type: document
doc-id: FW-COD
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# Coding Standard

## 1. Language & Compiler

| Parameter | Value |
|-----------|-------|
| Language | C11 / C++17 (mixed codebase) |
| Compiler | arm-none-eabi-gcc 12.x (NuttX target), gcc/clang (SITL) |
| Warning Level | `-Wall -Wextra -Werror` (CI enforced) |
| Static Analysis | `cppcheck`, `clang-tidy`, custom CI checks |
| MISRA Compliance | Not formally enforced; PX4 coding style + `-Werror` serves as guard |

## 2. Naming Conventions

| Element | Convention | Example |
|---------|-----------|--------|
| File names | `PascalCase.cpp` / `.hpp` (modules), `snake_case.c/.h` (NuttX/drivers) | `ICM42688P.cpp`, `sensor_accel.h` |
| C++ Classes | `PascalCase` | `MulticopterRateControl` |
| Methods | `camelCase()` | `publishAttitude()` |
| Member variables | `_snake_case` (leading underscore) | `_sensor_accel_pub` |
| Local variables | `snake_case` | `accel_sample` |
| Constants / Macros | `UPPER_SNAKE_CASE` | `MAX_MOTOR_COUNT` |
| uORB structs | `snake_case_s` | `sensor_accel_s` |
| Params | `UPPER_SNAKE_CASE` | `MC_ROLLRATE_P`, `EKF2_HGT_REF` |
| Enums (C++) | `PascalCase` values in scoped enum | `VehicleStatus::ARMING_STATE_ARMED` |

## 3. File Structure (C++ Module)

```cpp
/**
 * @file    MulticopterRateControl.cpp
 * @brief   Multicopter angular rate controller
 *
 * @author  PX4 Development Team
 * @license BSD-3-Clause
 */

#include "MulticopterRateControl.hpp"

#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/log.h>
#include <uORB/topics/sensor_gyro.h>

using namespace time_literals;

MulticopterRateControl::MulticopterRateControl() :
    ModuleParams(nullptr),
    ScheduledWorkItem(MODULE_NAME, px4::wq_configurations::rate_ctrl)
{
}

void MulticopterRateControl::Run()
{
    // Called by work queue at IMU DRDY rate
}
```

## 4. Key Code Patterns

### ModuleBase / WorkItem Pattern

Every PX4 module inherits from `ModuleBase<T>` and/or `ScheduledWorkItem`:

```cpp
class MyModule : public ModuleBase<MyModule>,
                 public ModuleParams,
                 public ScheduledWorkItem
{
public:
    static int task_spawn(int argc, char *argv[]);
    static int custom_command(int argc, char *argv[]);
    static int print_usage(const char *reason = nullptr);

    void Run() override;
};
```

### Parameters via DEFINE_PARAMETERS

```cpp
DEFINE_PARAMETERS(
    (ParamFloat<px4::params::MC_ROLLRATE_P>) _roll_rate_p,
    (ParamFloat<px4::params::MC_ROLLRATE_I>) _roll_rate_i,
    (ParamFloat<px4::params::MC_ROLLRATE_D>) _roll_rate_d
)
```

## 5. Forbidden Practices

| Practice | Reason | Alternative |
|----------|--------|------------|
| `malloc()` / `new` after init phase | Fragmentation on NuttX | Pre-allocate in `init()`, use static buffers |
| Recursive functions | Stack overflow on 4–12 KB stacks | Iterative approach |
| Direct HW register access in modules | Breaks SITL portability | Use NuttX device interface (`open/read/ioctl`) |
| `printf()` in flight code | Blocks, not thread-safe | Use `PX4_INFO()` / `PX4_ERR()` macros |
| Global mutable state | Race conditions across work queues | uORB topics for shared state |
| `#pragma once` omission | Double-include bugs | Always use `#pragma once` in headers |
| `sleep()` in `Run()` | Blocks entire work queue | Use `ScheduleOnInterval()` / `ScheduleDelayed()` |

## 6. Code Review Checklist (PX4)

- [ ] Follows PX4 naming convention (class=PascalCase, member=_snake_case)
- [ ] No compiler warnings with `-Wall -Wextra -Werror`
- [ ] All uORB publications have correct timestamp (`hrt_absolute_time()`)
- [ ] `Run()` is non-blocking (< 1 ms for rate controllers)
- [ ] Parameters declared via `DEFINE_PARAMETERS` macro
- [ ] Unit tests pass (`make tests`)
- [ ] SITL flight test validates behavior change

## Appendix A — MISRA C:2012 Subset (Flight-Critical Modules)

The following MISRA C:2012 rules are **mandatory** for flight-critical modules (`ekf2`, `mc_rate_control`, `mc_pos_control`, `commander`, `control_allocator`). Deviations require an approved DR (Deviation Record).

| Rule | Category | Description |
|------|----------|-------------|
| Rule 1.3 | Required | No undefined or critically unspecified behaviour |
| Rule 8.13 | Advisory | Pointer to const if object not modified |
| Rule 10.1 | Required | Operands shall not be of an inappropriate essential type |
| Rule 11.3 | Required | Cast shall not be performed between pointer to object and integer |
| Rule 12.2 | Required | Shift operand in range |
| Rule 13.5 | Required | No persistent side-effects in `&&` / `||` operand |
| Rule 14.3 | Required | Controlling expression shall not be invariant |
| Rule 15.7 | Required | All `if…else if` constructs shall have `else` |
| Rule 17.7 | Required | Return value of non-void function shall be used |
| Rule 21.3 | Required | `<stdlib.h>` dynamic allocation (`malloc`, `free`) prohibited |
| Rule 21.6 | Required | `<stdio.h>` I/O functions prohibited (use `PX4_INFO` macros) |
| Dir 4.1 | Required | Run-time failures shall be minimised |

> **Enforcement**: `clang-tidy` with MISRA profile runs in CI for listed modules. See `.clang-tidy` in repo root.

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
