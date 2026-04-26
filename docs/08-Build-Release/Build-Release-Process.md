---
title: "Build & Release Process"
type: document
doc-id: BRP
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# Build & Release Process

## 1. Build Pipeline

```
[Source (GitHub)] → [CMake Configure] → [Compile] → [Unit Test] → [SITL Smoke] → [.px4 Binary] → [Release Tag]
```

### Build Steps

| Step | Tool | Trigger | Pass Criteria |
|------|------|---------|--------------|
| Static Analysis | `cppcheck` + `clang-tidy` | Every PR | Zero new violations |
| Compile (target) | `arm-none-eabi-gcc` 12.x via CMake | Every push | Zero warnings (`-Werror`) |
| Compile (SITL) | Host gcc/clang via CMake | Every push | Zero warnings |
| Unit Test | Google Test (`make tests`) | Every push | 100% pass |
| SITL Smoke Test | PX4 SITL + jMAVSim (CI) | Every PR merge | Takeoff + hover + land pass |
| Binary Generation | CMake → `.px4` firmware package | Merge to `main` | Valid `.px4` file (contains `.bin` + metadata JSON) |
| Signing | Not enforced in v1.16 (bootloader CRC only) | Release build | CRC verified by bootloader |

### Build Commands

```bash
# Target build (Pixhawk v6X)
make px4_fmu-v6x_default

# SITL build (Gazebo)
make px4_sitl gazebo-classic

# Unit tests (host)
make tests

# Board config menu
make px4_fmu-v6x_default boardconfig
```

## 2. Build Configurations

| Config | CMake Target | Optimization | Debug | Asserts | Use Case |
|--------|-------------|-------------|-------|---------|----------|
| Default | `px4_fmu-v6x_default` | `-O2` | Partial | Enabled | Production flight |
| Debug | `px4_fmu-v6x_debug` | `-O0 -g` | Full symbols | Enabled | GDB debugging |
| SITL | `px4_sitl` | `-O0 -g` | Full | Enabled | Host simulation |
| Bootloader | `px4_fmu-v6x_bootloader` | `-Os` | Stripped | Minimal | Bootloader only |

## 3. Release Gate Checklist

Before any release:

- [ ] All unit tests pass (`make tests`)
- [ ] `cppcheck` + `clang-tidy` clean
- [ ] SITL smoke tests pass (all vehicle types: MC, FW, VTOL)
- [ ] HITL test on Pixhawk v6X hardware passes
- [ ] No open Critical/Major defects in GitHub Issues
- [ ] All PRs reviewed and merged
- [ ] `CHANGELOG.md` updated
- [ ] Release note written (`Release-Notes/`)
- [ ] `main` branch tagged with `v1.16.X`
- [ ] `.px4` binary uploaded to GitHub Releases

## 4. Release Artifact Package

| Artifact | Format | Naming | Destination |
|----------|--------|--------|------------|
| Firmware package | `.px4` | `px4_fmu-v6x_default-v1.16.1.px4` | GitHub Releases |
| Firmware binary | `.bin` (inside .px4) | Extracted at flash time | Bootloader upload |
| Release note | `.md` | `RELEASE-v1.16.1-2025-02-01.md` | `Release-Notes/` |
| Parameter metadata | `parameters.json` | Build artifact | QGC param editor |

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
