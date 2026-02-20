// Phase 1 — TNR 循环实现骨架（伪实现）
#pragma once
#include <vector>
// 真实实现应包含 Phase1_Structures 的头文件

// 伪定义，真实实现应使用具体的 DecoratedTensor、Block 等类型
struct DecoratedTensorLite {
  int dummy; // 占位
};

class Phase1_TNR_Skeleton {
public:
  Phase1_TNR_Skeleton(int d_per_sector);
  void initialize(/* lattice + symmetry params */);
  DecoratedTensorLite contractRegion(int region_id);
  DecoratedTensorLite applySymmetry(const DecoratedTensorLite& A_R);
  DecoratedTensorLite coarseGrain(const DecoratedTensorLite& A_R_dec,
                                  const std::vector<DecoratedTensorLite>& neighbors);
  std::vector<DecoratedTensorLite> decomposeIntoBlocks(const DecoratedTensorLite& A_R_coarse);
  DecoratedTensorLite truncateBlocks(const std::vector<DecoratedTensorLite>& blocks,
                                     int D_per_sector);
  DecoratedTensorLite assembleNext(const std::vector<DecoratedTensorLite>& blocks_truncated);
  void updateLattice(const DecoratedTensorLite& A_R_next);
  bool checkConvergence();
  void run(int max_iters, double tolerance);
private:
  int D_per_sector_;
};
