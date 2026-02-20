# Phase 1 — TNR 循环骨架（DTNR 的实现骨架）

- 目标：给出一个模块化的 TNR 循环骨架，便于后续实现阶段直接填充具体数值计算细节。
- 核心模块：
- RegionContractor：负责局部区域收缩并产生 A_R_dec
- SymmetryProjector：对 A_R_dec 做对称性投影
- CoarseGrainer：对 A_R_dec 进行粗化，输出 A_R_coarse
- BlockSplitter：把粗化后的张量按对称性分块并建立子块
- Truncator：对每个分块执行 SVD+截断
- Assembler：从分块组装回一个新的区域张量 A_R_next
- LatticeUpdater：将 A_R_next 更新回全局晶格
- ConvergenceChecker：判断是否达到收敛
- ObservablesRecorder：记录 RG 观测值与收敛指标

- 数据结构：DecoratedTensor、Block、BlockBlock（按对称性分块）等
- 流程概览：
- 初始化 -> 循环开始 -> 区域收缩 -> 对称性投影 -> 粗化 -> 分块 & 截断 -> 重组 -> 更新晶格 -> 收敛性判定 -> 记录 -> 结束
