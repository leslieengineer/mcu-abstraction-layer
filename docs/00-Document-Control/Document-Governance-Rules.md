---
title: "Document Governance Rules"
type: document
doc-id: DOC-GOV
version: "1.0"
status: released
---

# Document Governance Rules

## 1. Document Lifecycle

```
Draft → Under Review → Approved → Released → Superseded → Archived
```

| State | Description | Who Can Edit |
|-------|-------------|-------------|
| **Draft** | Initial creation | Author |
| **Under Review** | Sent for peer review | Author (based on feedback) |
| **Approved** | Reviewed and signed off | Only via change request |
| **Released** | Baselined for external use | Only via change request |
| **Superseded** | Replaced by newer version | No edits — move to `99-Archive/` |
| **Archived** | No longer applicable | Read-only |

## 2. Versioning Rules

- Use **Major.Minor** format: `1.0`, `1.1`, `2.0`
- **Major**: Breaking changes, scope changes, re-baseline
- **Minor**: Corrections, clarifications, additions
- Draft versions use `0.x` (e.g., `0.1`, `0.2`)

## 3. Review Process

1. Author creates/modifies document
2. Author updates frontmatter `version` and `status: under-review`
3. Reviewer checks content against template and governance rules
4. On approval: status → `approved`, record in `CHANGELOG.md`
5. On rejection: author revises, repeat from step 2

## 4. Frontmatter Requirements

Every Markdown document MUST include YAML frontmatter with:

```yaml
---
title: "Document Title"
type: document | readme | template | register | log
doc-id: PROJECT-XXX        # Unique identifier
version: "1.0"
status: draft | under-review | approved | released | archived
created: YYYY-MM-DD
last-updated: YYYY-MM-DD
author: Name
reviewer: Name
---
```

## 5. Change Request Process

For **approved** or **released** documents:

1. Raise change request in `Decision-Log.md` or project tracker
2. Document change rationale
3. Create new version (increment version number)
4. Follow review process (Section 3)
5. Record in `CHANGELOG.md`

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
