#include <omp.h>
#include <stdio.h>
#include "utils.h"

double inner0(long n, double* v, double* w) {
  double prod = 0;
  for (long i = 0; i < n; i++) prod += v[i] * w[i];
  return prod;
}

double inner1(long n, double* v, double* w) {
  int p = omp_get_max_threads();
  double* partial_sum = (double*) malloc(p * sizeof(double));

  #pragma omp parallel
  {
    int tid = omp_get_thread_num();
    double local_prod = 0;
    #pragma omp for
    for (long i = 0; i < n; i++) {
      local_prod += v[i] * w[i];
    }
    partial_sum[tid] = local_prod;
  }

  double sum = 0;
  for (int i = 0; i < p; i++) sum += partial_sum[i];
  free(partial_sum);

  return sum;
}

double inner2(long n, double* v, double* w) {
  double prod = 0;
  #pragma omp parallel for reduction(+:prod)
  for (long i = 0; i < n; i++) prod += v[i] * w[i];
  return prod;
}

int main(int argc, char** argv) {
  Timer t;
  long n = read_option<long>("-n", argc, argv);
  long repeat = read_option<long>("-repeat", argc, argv, "1");

  double* x = (double*) malloc(n * sizeof(double));
  double* y = (double*) malloc(n * sizeof(double));
  for (long i = 0; i < n; i++) {
    x[i] = i+1;
    y[i] = 2.0 / (i+1);
  }

  t.tic();
  double x_dot_y = 0;
  for (long p = 0; p < repeat; p++) {
    x_dot_y += inner2(n, x, y);
  }
  printf("inner-product = %f\n", x_dot_y);
  printf("time elapsed = %f\n", t.toc());

  printf("%f GB/s\n", repeat * 2 * n * sizeof(double) / 1e9 / t.toc());
  printf("%f Gflop/s\n", repeat * 2 * n / 1e9 / t.toc());

  free(x);
  free(y);

  return 0;
}
