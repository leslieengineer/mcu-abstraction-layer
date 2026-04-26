---
title: "Quality & Test"
type: readme
folder: 07-Quality-Test
---

# 07 — Quality & Test

> Verification, validation, compliance, and defect management.

## Contents

| File | Purpose | IEEE Ref |
|------|---------|----------|
| [VnV-Strategy.md](VnV-Strategy.md) | V&V approach, coverage targets | IEEE 1012 |
| [Test-Plan.md](Test-Plan.md) | Master test plan (STP) | IEEE 829 |
| [Defect-Taxonomy-RCA.md](Defect-Taxonomy-RCA.md) | Defect classification & root cause analysis | — |
| [Compliance-Matrix.md](Compliance-Matrix.md) | Standard compliance evidence tracking | — |
| [Test-Cases/](Test-Cases/README.md) | Individual test case files | IEEE 829 |

## V-Model Mapping

```
Requirements ───────────────────────── Acceptance Test
    │                                       │
    ▼                                       ▼
System Design ──────────────────── System Test
    │                                       │
    ▼                                       ▼
Module Design ──────────────── Integration Test
    │                                       │
    ▼                                       ▼
    Coding ────────────────── Unit Test
```
