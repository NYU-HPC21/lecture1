// Timing and calculating floating-point operations (flop/s)
// $ g++ -std=c++11 -O3 00-compute.cpp && ./a.out
// $ cat /proc/cpuinfo
// $ sysctl -n machdep.cpu.brand_string # on Mac
// $ htop
// calculate theoretical maximum flop/s
// calculate expected flop/s -- latency and throughput : https://software.intel.com/sites/landingpage/IntrinsicsGuide/#

#include "utils.h"

int main(int argc, char** argv) {
  long n = 1000000000;
  Timer t;

  double x, y;
  x = 0;
  y = 1;

  t.tic();
  for (long i = 0; i < n; ++i) {
    x = x * 0.5 + y;
  }
  printf("wall-time = %f s\n", t.toc());
  printf("flop-rate = %f Gflop/s\n", 2 * n / 1e9 / t.toc());

  printf("x = %f\n", x);
  return 0;
}
