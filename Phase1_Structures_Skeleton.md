Phase 1 — SU(2)_k 自旋网结构骨架（数据结构草案）

说明
- 该文件给出一个可实现语言无关的接口骨架，便于后续在 C/C++/Rust/Python 中落地实现。

1) SpinNetwork（自旋网络）
- 成员示例：
  - edges: 含有边的集合及其自旋标签
  - vertices: 顶点集合及其连接关系
- 关键操作（接口草案，待实现）：
  - addEdge(a, b, j): 连接两个节点，并指定自旋标签 j
  - setEdgeLabel(edge_id, j)
  - contractSubgraph(subgraph): 对子图进行张量化以用于粗化步骤
  - fuseEdges(edge_ids): 将若干边按规则融合

2) Tensor（基础张量）
- 模板化数据类型：Tensor<T>
- 关键操作（接口草案）：
  - dim(), reshape(new_shape), contract(Tensor other), transpose(), clone()
- 属性：shape、data

3) Intertwiner（互换子）
- 描述：将多条边的表示耦合为一个新的边/与量子群的表示兼容
- 成员：indices、allowed_representations、fusion_rules
- 操作：bind(incoming_edges, outgoing_edges)

4) DecoratedTensor（装饰张量）
- 字段：
  - T: Tensor
  - face_labels: 面的 j_f 索引序列
  - irrep_labels: 边/块的不可约表示标签
  - intertwiner_labels: 连接边的 Intertwiner 标签
  - metadata: 包含对称性投影、Gauss 定律信息等

5) Phase1_Structures.md（接口草案）
- 提供上述类的初步接口定义、成员变量及简要注释
- 便于后续实现与单元测试
