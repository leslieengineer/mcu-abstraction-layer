---
title: "Build & Release"
type: readme
folder: 08-Build-Release
---

# 08 — Build & Release

> CI/CD pipeline, versioning strategy, and release management.

**PX4 v1.16 context**: PX4 uses GitHub Actions CI with NuttX cross-compilation (`arm-none-eabi-gcc 12.x`), SITL regression tests, and a tag-based release flow. Firmware binaries are published to GitHub Releases and the QGroundControl firmware update server.

## Contents

| File | Purpose |
|------|---------|
| [Build-Release-Process.md](Build-Release-Process.md) | Build pipeline, release gates, sign-off |
| [Versioning-Branching.md](Versioning-Branching.md) | Semantic versioning, branch strategy |
| [Release-Notes/](Release-Notes/README.md) | Per-release notes |
