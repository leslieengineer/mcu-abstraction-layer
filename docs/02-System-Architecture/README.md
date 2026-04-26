---
title: "System Architecture"
type: readme
folder: 02-System-Architecture
---

# 02 — System Architecture

> System-level design decisions, context diagrams, and Architecture Decision Records.

## Contents

| File | Purpose | IEEE Ref |
|------|---------|----------|
| [System-Context.md](System-Context.md) | C4 context & container diagrams | ISO 42010 |
| [ADR/ADR-Index.md](ADR/ADR-Index.md) | Index of all Architecture Decision Records | — |

## Architecture Views

This folder follows the **C4 Model** approach:
1. **Context** — System boundary and external actors (in `System-Context.md`)
2. **Container** — High-level technology blocks (in `System-Context.md`)
3. **Component** — Internal module breakdown (in `05-Firmware-Design/`)
4. **Code** — Implementation details (in source code repository)

## Mục đích và ý nghĩa

Tài liệu `02-System-Architecture` dùng để đặt nền tảng cho mọi quyết định thiết kế hệ thống, nhất là khi bạn xây dựng một abstract layer dùng chung cho nhiều loại MCU. Ở đây, bạn xác định:

- ranh giới hệ thống và các tác nhân bên ngoài tương tác với dự án
- các phần mềm/công nghệ chính chịu trách nhiệm xử lý dữ liệu và giao tiếp
- các yêu cầu chất lượng như tin cậy, hiệu năng, bảo mật, tính mở rộng

Khi mục tiêu của bạn là làm một abstraction layer hỗ trợ nhiều MCU, phần `System Context` càng quan trọng vì nó giúp bạn:

- xác định những giao diện chung cần hỗ trợ cho nhiều nền tảng
- tránh gắn nhầm chi tiết phần cứng vào lớp trừu tượng
- giữ cho thiết kế rõ ràng giữa phần abstraction chung và phần cụ thể cho MCU

## Companion Diagrams

Store `.drawio` files in `00-Document-Control/Companion-Formats/diagrams-drawio/`
Store `.puml` files in `00-Document-Control/Companion-Formats/uml-puml/`
