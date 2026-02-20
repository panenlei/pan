# Phase 1 — Dittrich 2016 伪代码草案（DTNR 相关）

- 目标：将 Dittrich 2016 的核心算法以伪代码方式表达，便于后续实现映射
- 伪代码要点：参照 DTNR 的区域收缩、对称性投影、块分解与截断、RG 循环、固定点判据
  - 数据结构：DecoratedTensor（T、face_labels、irrep_labels、intertwiner_labels、metadata）
  - 过程：初始化、区域收缩、对称性投影、粗化、分块截断、更新、收敛判断
- 产出：phase1_Dittrich_v1.md 与 phase1/pseudo_code_v1.md 的对照引用
