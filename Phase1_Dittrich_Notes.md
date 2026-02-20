# Phase 1 — Dittrich 2016 核心笔记

- 论文：Bianca Dittrich, Sebastian Mizera, Sebastian Steinhaus, “Decorated tensor network renormalization for lattice gauge theories and spin foam models”, New Journal of Physics 18 (2016) 053009 [arXiv:1409.2407]
- 核心贡献：提出装饰张量网络重整化（DTNR）算法，能够在粗化过程中显式保持规范对称性，并能解释/识别固定点张量。
- 关键点：
  - 通过装饰结构编码局部对称性和耦合关系，确保对称性在多尺度传播中不被破坏
  - 将区域张量收缩与对称性分块结合，采用块级 SVD 进行降维与截断
  - 固定点可解释性来自对称性分块的保持，便于识别拓扑/对称性保护相
- 伪代码对照：建议将 Dittrich 的步骤映射到 Phase1_ToDo.md 的任务中，先产出 phase1/pseudo_code_v1.md 作为实现草案。
