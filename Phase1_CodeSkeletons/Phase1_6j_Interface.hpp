// Phase 1 — 6j 符号接口骨架（C++ 风格）
// 仅提供接口草案，方便后续实现对接
#pragma once
#include <complex>
#include <string>

namespace pnt_phase1 {
class SixJInterface {
public:
  // 计算 q-变形的六阶符号
  // k 为 SU(2)_k 的等级，j1..j6 为自旋标签（整数或半整数，约定实现中编码为整数）
  static std::complex<double> compute6j(int j1, int j2, int j3, int j4, int j5, int j6, int k);

  // 缓存接口（简单实现，后续可替换为更高效的缓存方案）
  static bool loadCache(const std::string& path);
  static bool saveCache(const std::string& path);
};
}
