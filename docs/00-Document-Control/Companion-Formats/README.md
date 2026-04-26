---
title: "Companion Formats"
type: readme
folder: Companion-Formats
---

# Companion Formats

> Non-Markdown files that accompany the main documentation.
> Each sub-folder holds one format type. Never mix formats.

## Sub-Folders

| Folder | Format | Purpose | Tool |
|--------|--------|---------|------|
| `diagrams-drawio/` | `.drawio` | Architecture, block, flow diagrams | draw.io / diagrams.net |
| `exports-pdf/` | `.pdf` | Baselined PDF snapshots for audit | Any PDF exporter |
| `matrices-csv/` | `.csv` | Traceability, risk, requirements matrices | Excel / scripts |
| `registers-xlsx/` | `.xlsx` | Workbooks, checklists, scoring | Excel |
| `uml-puml/` | `.puml` | Sequence, class, state diagrams | PlantUML |

## Rules

1. **Markdown is primary** — companion files supplement, never replace prose docs
2. **Name files** to match the related Markdown document (e.g., `system-context.drawio` ↔ `System-Context.md`)
3. **PDF exports** include version in filename: `PRD-v1.0.pdf`
4. **CSV files** must have a header row; use UTF-8 encoding
5. **Do not store** generated/binary files that can be rebuilt from source
