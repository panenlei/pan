# Phase 1 — TNR 循环实现骨架（伪实现）

- 目标：提供一个模块化、面向对象的 TNR 循环骨架，便于后续填充具体实现。
- 结构与接口（伪实现）：
- class Phase1_TNR:
-   public:
-     Phase1_TNR(int D_per_sector);
-     void initialize(lattice, G);
-     DecoratedTensor contract_region(const LatticeBlock& region);
-     DecoratedTensor apply_symmetry(const DecoratedTensor& A_R);
-     DecoratedTensor coarse_grain(const DecoratedTensor& A_R_dec, const std::vector<DecoratedTensor>& neighbors);
-     std::vector<Block> decompose_into_blocks(const DecoratedTensor& A_R_coarse);
-     DecoratedTensor truncate_blocks(const std::vector<Block>& blocks, int D_per_sector);
-     DecoratedTensor assemble_next(const std::vector<Block>& blocks_truncated);
-     void update_lattice(const DecoratedTensor& A_R_next);
-     bool check_convergence();
-     void run(int max_iters, double tolerance);

- 数据与类型：需要与 Phase1_Structures.md 中的 SpinNetwork、Tensor、Intertwiner、DecoratedTensor 等结构对齐。
- 备注：此文档仅作骨架，后续将具体实现细化到语言级代码与单元测试。
