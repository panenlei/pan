// Phase 1 — 6j 符号接口实现（真实实现草案，接入 sl2cfoam-next 的封装）
#include <iostream>
#include "Phase1_6j_Interface.hpp"
#include <unordered_map>
#include <mutex>
#include <cmath>

// 针对 sl2cfoam-next 的可能导出值进行绑定
extern "C" {
  double wigner_6j(int j1, int j2, int j3, int j4, int j5, int j6);
  double wigner_6j_q(int j1, int j2, int j3, int j4, int j5, int j6, double q);
}

namespace {
  std::unordered_map<uint64_t, double> cache6j;
  std::mutex mtx6j;
uint64_t make_key(int j1,int j2,int j3,int j4,int j5,int j6,int k){
    // 简单拼接为 64 位键
    uint64_t key = 0;
    key = (key << 8) | (uint64_t)(j1 & 0xFF);
    key = (key << 8) | (uint64_t)(j2 & 0xFF);
    key = (key << 8) | (uint64_t)(j3 & 0xFF);
    key = (key << 8) | (uint64_t)(j4 & 0xFF);
    key = (key << 8) | (uint64_t)(j5 & 0xFF);
    key = (key << 8) | (uint64_t)(j6 & 0xFF);
    key = (key << 8) | (uint64_t)(k & 0xFF);
    return key;
}
}

std::complex<double> compute6j(int j1, int j2, int j3, int j4, int j5, int j6, int k){
  uint64_t key = make_key(j1,j2,j3,j4,j5,j6,k);
  {
    std::lock_guard<std::mutex> lock(mtx6j);
    auto it = cache6j.find(key);
    if (it != cache6j.end()) return std::complex<double>(it->second, 0.0);
  }
  double result = 0.0;
  if (k == 0) {
    result = wigner_6j(j1,j2,j3,j4,j5,j6);
  } else {
    double q = std::cos(2.0 * M_PI / (k + 2.0));
    result = wigner_6j_q(j1,j2,j3,j4,j5,j6, q);
  }

  std::complex<double> res = std::complex<double>(result, 0.0);
  {
    std::lock_guard<std::mutex> lock(mtx6j);
    cache6j[key] = result;
  }
  return res;
}

bool loadCache(const std::string& cacheFile){
  // TODO: implement HDF5 读取，当前版本为占位实现
  (void)cacheFile;
  return false;
}

void saveCache(const std::string& cacheFile){
  // TODO: implement HDF5 写入，当前版本为占位实现
  (void)cacheFile;
}

void precomputeAll6j(int k, const std::string& /*cacheFile*/ = "6j_cache.h5") {
  int max_j = (k > 0 ? (k - 2) / 2 : 0);
  for (int j1=0; j1<=max_j; ++j1)
    for (int j2=0; j2<=max_j; ++j2)
      for (int j3=0; j3<=max_j; ++j3)
        for (int j4=0; j4<=max_j; ++j4)
          for (int j5=0; j5<=max_j; ++j5)
            for (int j6=0; j6<=max_j; ++j6) {
              compute6j(j1,j2,j3,j4,j5,j6,k);
            }
  // 未来可将缓存持久化到 cacheFile
}
