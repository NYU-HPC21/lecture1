// Timing and calculating floating-point operations (flop/s)
// $ g++ -std=c++11 -O3 01-compute.cpp && ./a.out
// $ cat /proc/cpuinfo
// $ sysctl -n machdep.cpu.brand_string # on Mac
// $ htop
// calculate theoretical maximum flop/s
// calculate expected flop/s -- latency and throughput : https://software.intel.com/sites/landingpage/IntrinsicsGuide/#

#include "utils.h"

int main(int argc, char** argv) {
  constexpr int M = 1;
  long n = 1000000000;
  Timer t;

  double x[M], y[M];
  for (int i = 0; i < M; i++) {
    x[i] = 0;
    y[i] = i+1;
  }

  t.tic();
  for (long i = 0; i < n; ++i) {
    for (long j = 0; j < M; j++) {
      x[j] = x[j] * 0.5 + y[j];
    }
  }
  printf("wall-time = %f s\n", t.toc());
  printf("flop-rate = %f Gflop/s\n", 2 * M * n / 1e9 / t.toc());

  double sum = 0;
  for (int i = 0; i < M; i++) sum += x[i];
  printf("x = %f\n", sum);
  return 0;
}
