# Phase 1 Repro & Borrowed Implementation Plan — 详细实施方案

目标
- 参考 Dittrich 2016 的实现细节，给出 SU(2)_k 自旋网在 DTNR 框架下可复现的实现路线，包含 6j 符号接口、对称性保持策略以及粗化流程的具体实现要点。

核心设计原则
- 保持对称性约束在多尺度传播中的可追踪性；
- 将论文中的区域收缩、分块投影、粗化与截断分解为模块化接口；
- 使用明确的输入输出协议以便单元测试与对照实验。

关键子任务（阶段性落地）
- 1) 解析模型结构与数据标签
   - 列出区域张量输入输出的形状、标签含义（j_f、j、intertwiner、irrep 等）
   - 给出一个简单的示例网格及标签分配。
- 2) 6j 符号查询接口设计
   - 设计函数签名：compute6j(j1, j2, j3, j4, j5, j6, k) -> complex
   - 增加缓存机制：本地缓存表、键值对结构、文件格式（如 HDF5）
- 3) DecoratedTensor 的分块策略
   - 设计按对称性分块的分区定义、每个分块的张量形状、保留维度
- 4) TNR 循环的模块化实现
   - region_contract(A_R)：区域收缩，输出局部装饰张量 A_R
   - apply_symmetry(A_R, G)：对称性投影/分块
   - coarse_grain(A_R_dec, neighbors)：粗化并保持对称标签
   - decompose_and_truncate(A_R_coarse, D_per_sector)：按区块分解并截断
   - assemble_next(A_R_blocks)：组装成下一尺度的张量
- 5) 收敛性与对比测试
   - 定义收敛判据（如 max_norm 差小于 tolerance），记录谱半径等辅助指标
- 6) 输出与验证
   - 产出 Phase1_Repro_Detail.md 作为实施细则，Phase1_6j_Interface.md 作为接口设计草案

输出物清单
- Phase1_Repro_Detail.md（详细实施细则）
- Phase1_6j_Interface.md（6j 符号查询接口设计）
- Phase1_TNR_Skeleton.md（TNR 循环骨架）
