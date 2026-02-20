// Lightweight test harness for 6j interface (CLI style, not using Catch2 by default)
#include <iostream>
#include <complex>
#include "../Phase1_CodeSkeletons/Phase1_6j_Interface.hpp"

int main() {
  using namespace pnt_phase1;
  // Classical SU(2) case
  std::complex<double> a = SixJInterface::compute6j(0,0,0,0,0,0,0);
  if (std::abs(a.real() - 1.0) > 1e-12 || a.imag() != 0.0) {
    std::cerr << "Test failed: expected 1+0i, got " << a << std::endl;
    return 1;
  }
  // Basic non-zero test: ensure function returns a finite complex
  auto b = SixJInterface::compute6j(1,1,1,1,1,1,0);
  if (!std::isfinite(b.real()) || !std::isfinite(b.imag())) {
    std::cerr << "Test failed: non-finite result" << std::endl;
    return 1;
  }
  std::cout << "Phase1_6j_Interface basic tests passed" << std::endl;
  return 0;
}
