---
title: "AI Governance"
type: readme
folder: 11-AI-Governance
---

# 11 — AI Governance

> Rules and constraints for AI-assisted development in this project.
> Ensures AI tools (Copilot, ChatGPT, Cursor, etc.) produce code that meets project standards.

## Contents

| File | Purpose |
|------|---------|
| [AI-Mandatory-Rules.md](AI-Mandatory-Rules.md) | Hard constraints AI agents MUST follow |
| [AI-Code-Review-Checklist.md](AI-Code-Review-Checklist.md) | Review criteria for AI-generated code |

## Why This Exists

AI-generated code in embedded systems carries extra risk:
- **Safety**: Wrong register config → hardware damage
- **Reliability**: Subtle race conditions in RTOS code
- **Security**: Weak crypto, hardcoded keys, buffer overflows
- **Compliance**: Code must meet MISRA, IEC, etc.

Human review of AI output is **mandatory**.
