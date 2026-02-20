DTNR 在 SU(2)_k 自旋网络中的复现步骤（2.2）

- 目标
- 复现 Dittrich 等人（2016）关于装饰张量网络重整化在格子规范理论与自旋泡沫模型中的核心算法，聚焦对称性保持与固定点张量的识别。

- 前提条件
- 知识：基于 2.1 的理论基础
- 数据：选定 k 的预计算六阶符号（如 k=4 的 sixj_k4.h5）
- 工具：支持分块稀疏运算与逐块 SVD 的张量库；可脚本化环境
- 资源：基线 MVP 规模（k=4，j_max=1，网格 8^3）

- Step-by-step plan
- 1) 定义模型与数据结构
- - Set k, j_max = (k-2)/2, grid (e.g., 8^3)
- - Define representation labels: j_f in {0, 1/2, ..., (k-2)/2}
- - Define DecoratedTensor data structure with fields: T, face_labels, irrep_labels, intertwiner_labels, metadata
- - Load precomputed sixj data (precomputed_sixj)
- 2) Initialize decorated tensors
- - 为每个局部区域构建初始 T，带有相应的标签
- - 附加对称性标签，检查融合规则
- 3) Local region contraction with symmetry preservation
- - 1) 收缩区域张量，得到 A_R_dec
- - 2) 应用对称性约束投影，保持 Gauss 律等约束
- 4) Coarse-graining with symmetry
- - 1) 粗化并保留对称性标签
- - 2) 按对称性分块，进行 SVD 与截断
- - 3) 将块重新组装成 A_R_next
- 5) Lattice update and iteration control
- - 更新晶格，计算收敛性指标
- - 记录观测量
- 6) Fixed-point identification and interpretation
- - 识别尺度不变的对称性结构
- 7) Validation and comparison
- - 与参考结果对照，验证可重复性
- 8) Deliverables
- - MVP 数据、RG 日志、可复现实验记录
- 9) Risk management
- - 数据可用性、数值稳定性、资源消耗
- 10) 结束

- Set k, j_max = (k-2)/2, grid (e.g., 8^3)
- Define representation labels: j_f in {0, 1/2, ..., (k-2)/2}
- Define DecoratedTensor data structure with fields: T, face_labels, irrep_labels, intertwiner_labels, metadata
- Load precomputed sixj data (precomputed_sixj)

2) Initialize decorated tensors
- For each local region, build initial T using vertex amplitudes with corresponding 6j_q inputs
- Attach symmetry labels to tensor indices
- Verify fusion rules and block structure consistency

3) Local region contraction with symmetry preservation (Step 2.1 core)
- Contract tensors within a region to form A_R_dec
- Apply symmetry constraints: project A_R into allowed symmetry blocks (block-sparse projection)
- Validate that Gauss constraints are respected in A_R_dec

4) Coarse-graining with symmetry (Step 2.1 core)
- Coarse-grain A_R_dec with neighboring regions to produce A_R_next
- Decompose A_R_next into symmetry blocks: blocks = decompose_into_blocks(A_R_next, G)
- For each block, perform SVD: U, S, V = svd(block)
- Truncate within block to k = D_per_sector
- Reassemble truncated blocks into A_R_trunc and assemble A_R_next

5) Lattice update and iteration control
- Replace region tensors with A_R_next in lattice
- Track iteration count and compute diff = max_norm(prev_lattice - lattice)
- Converged when diff < tolerance
- Log observables: RG trajectory, block sizes, singular value spectra

6) Fixed-point identification and interpretation
- Inspect final decorated tensors for stable symmetry patterns
- Record fixed-point candidates that satisfy invariance under scale changes

7) Validation and comparison
- Compare RG trajectories against known reference results or analytic expectations
- If possible, reproduce specific fixed-point structures described in Dittrich 2016 examples

8) Deliverables
- MVP data: sixj_k4.h5, RG trajectories, delta metrics, fixed-point candidates
- Documentation: theory-to-implementation mapping notes, reproducibility checklist

9) Risk management
- Data availability: ensure sixj tables exist and are accurate
- Numerical stability: validate truncation thresholds; perform multiple random starts if feasible
- Resource constraints: monitor memory usage; consider smaller grids for debugging

Notes
- This plan emphasizes 2.1–2.2 steps as a blueprint for replication; adapt specifics to your codebase and library choices.

复现步骤结束（2.2）
