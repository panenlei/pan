装饰张量网络重整化（DTNR）伪代码

输入
- lattice：初始晶格结构与局部装饰张量
- G：对称群（如 SU(2)_k）
- D_per_sector：每个对称分区保留的最大维度
- max_iters：最大迭代次数
- tolerance：收敛容忍度
- precomputed_sixj：预计算的 6j 符号数据集（若已有则使用，否则需要外部数据）

数据结构
- DecoratedTensor：T、irrep_labels、intertwiner_labels、metadata
- BlockPS：按对称性分块的张量块集合
- LatticeBlock：子区域，包含内部装饰张量及边界装饰信息

核心流程：DTNR(lattice, G, D_per_sector, max_iters, tolerance, precomputed_sixj)
  // 初始化
  decorate_all_tensors(lattice, G)          // 为晶格中的张量附加表示索引与 intertwinier 索引
  compute_initial_blocks(lattice, G)         // 根据对称性划分块，生成初始 BlockPS
  iter = 0
  converged = false

  while (iter < max_iters) and (not converged):
    iter += 1

    // 步骤1: 局部区域装饰张量构建与对称性保持
    parallel_for each region R in lattice:
      A_R = contract_region_tensors(R)            // 区域内张量收缩，生成局部装饰张量
      A_R_dec = apply_symmetry_constraints(A_R, G) // 通过对称性投影/分块保持对称性

    // 步骤2: 区域粗化（保持对称性）
    parallel_for each region R in lattice:
      A_R_coarse = coarse_grain_region(A_R_dec, neighboring_decorated_tensors)

      // 步骤2.1: 按对称性分块，进行块级降维与截断
      blocks = decompose_into_blocks(A_R_coarse, G)      // 将张量按对称性分块，返回各分块张量
      for each block b in blocks:
        U, S, V = svd(block_b)                          // 块内 SVD
        k = min(D_per_sector, rank(S))                   // 截断维度
        block_b_trunc = truncate_to_dimension(block_b, k) // 截断
        store_truncated_block(b, block_b_trunc, U, V)     // 保存以构造下一个尺度的张量

      A_R_next = assemble_from_blocks(blocks)            // 组装截断后的块为新的区域张量
      save_coarse_tensor(R, A_R_next)

    // 步骤3: 更新晶格/网络结构
    lattice = update_lattice_with_coarse_tensors(lattice)

    // 步骤4: 收敛性判断
    diff = max_norm_difference_between_scales(previous_lattice, lattice)
    converged = (diff < tolerance)

    // 步骤5: 指标与可观测量记录
    record_RG_observables(lattice, iter)

  // 输出结果
  fixed_point_candidates = extract_fixed_point_structures(lattice)
  return {
    'lattice': lattice,
    'fixed_point_candidates': fixed_point_candidates,
    'iterations': iter,
    'converged': converged,
    'observables': retrieved_observables
  }

辅助子过程（简述）
- decorate_all_tensors(lattice, G)
- compute_initial_blocks(lattice, G)
- contract_region_tensors(R)
- apply_symmetry_constraints(A, G)
- coarse_grain_region(A_dec, neighbors)
- decompose_into_blocks(A_coarse, G)
- svd(block)
- truncate_to_dimension(block, k)
- assemble_from_blocks(blocks)
- update_lattice_with_coarse_tensors(lattice)
- max_norm_difference_between_scales(prev, curr)
- record_RG_observables(lattice, iter)
- extract_fixed_point_structures(lattice)

Notes
- 这是一个高层伪代码，聚焦数据结构与流程。要落地到 MVP，需要具体的张量形状、索引约定与实际的库实现。
