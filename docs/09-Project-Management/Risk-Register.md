---
title: "Risk Register"
type: register
doc-id: RMP
version: "1.0"
status: released
created: "2024-12-01"
last-updated: "2025-02-01"
author: "PX4 Dev Team"
reviewer: "Release Manager"
---

# Risk Register

## Risk Scoring

| Impact | Score |
|--------|-------|
| Critical | 5 |
| High | 4 |
| Medium | 3 |
| Low | 2 |
| Negligible | 1 |

| Likelihood | Score |
|-----------|-------|
| Almost Certain | 5 |
| Likely | 4 |
| Possible | 3 |
| Unlikely | 2 |
| Rare | 1 |

**Risk Score** = Impact × Likelihood (1–25)

## Register

| R-ID | Category | Risk Description | Impact | Likelihood | Score | Mitigation | Owner | Status |
|------|----------|-----------------|--------|-----------|-------|-----------|-------|--------|
| R-001 | Technical | EKF2 divergence under high vibration causes loss of position estimate | 5 | 3 | 15 | Dual-IMU voting, EKF2 innovation monitoring, auto-fallback to inertial-only | Navigation Lead | Mitigated |
| R-002 | Technical | DroneCAN ESC controller CAN bus saturation under high-rate commands | 4 | 2 | 8 | Rate-limit ESC commands to 200 Hz, CAN bus load monitoring | Drivers Lead | Mitigated |
| R-003 | Supply Chain | ICM-42688P IMU chip shortage (single source: TDK InvenSense) | 4 | 3 | 12 | Qualify BMI088 as alternate, maintain dual-driver support | HW Lead | Open |
| R-004 | Supply Chain | STM32H753 lead time > 40 weeks | 5 | 3 | 15 | Pre-order buffer stock, qualify STM32F765 fallback (Pixhawk v5X) | HW Lead | Open |
| R-005 | Compliance | EASA certification requires DO-178C evidence not yet produced | 5 | 4 | 20 | Engage DO-178C consultant, begin DAL-D evidence collection | PM | Open |
| R-006 | Schedule | Multi-platform (MC/FW/VTOL) testing requires 3x test cycles | 3 | 4 | 12 | Parallelize SITL regression, dedicate 1 week per vehicle type for HITL | Test Lead | Open |
| R-007 | Technical | MAVLink v2 message fragmentation on lossy telemetry links | 3 | 3 | 9 | Implement MAVLink 2.0 message signing + retransmission for critical msgs | Comms Lead | Mitigated |
| R-008 | External | GPS constellation degradation in contested environments | 4 | 2 | 8 | Multi-constellation support (GPS+GLONASS+Galileo), optical flow fallback | Navigation Lead | Open |

## Risk Categories

| Category | Examples |
|----------|---------|
| Technical | HW bug, FW complexity, performance gap |
| Schedule | Resource unavailable, scope creep, dependency delay |
| Supply Chain | Component EOL, lead time, single source |
| Compliance | Standard update, test facility unavailable |
| External | Customer change request, regulatory change |

## Review Cadence

- **Weekly**: Review open High/Critical risks
- **Bi-weekly**: Full register review
- **Milestone**: Formal risk review before each gate

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
