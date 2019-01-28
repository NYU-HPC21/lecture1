// $ mpic++ -std=c++11 -O3 -fopenmp 07-mpi-inner.cpp && mpirun -n 4 ./a.out -n 100000000 -repeat 10

#include <omp.h>
#include <mpi.h>
#include <stdio.h>
#include "utils.h"

double omp_inner(long n, double* v, double* w) {
  double prod = 0;
  #pragma omp parallel for reduction(+:prod)
  for (long i = 0; i < n; i++) prod += v[i] * w[i];
  return prod;
}

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);
  MPI_Comm comm = MPI_COMM_WORLD;

  int mpirank, mpisize;
  MPI_Comm_rank(comm, &mpirank);
  MPI_Comm_size(comm, &mpisize);

  Timer t;
  long n = read_option<long>("-n", argc, argv);
  long repeat = read_option<long>("-repeat", argc, argv, "1");

  long n_local = n / mpisize;
  long offset = n_local * mpirank;

  double* x = (double*)malloc(n_local * sizeof(double));
  double* y = (double*)malloc(n_local * sizeof(double));
  for (long i = 0; i < n_local; i++) {
    x[i] = 1.0 + offset + i;
    y[i] = 2.0 / (1.0 + offset + i);
  }

  t.tic();
  double prod = 0;
  for (long p = 0; p < repeat; p++){
    double local_prod = omp_inner(n_local, x, y);
    MPI_Reduce(&local_prod, &prod, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  }
  if (mpirank == 0) {
    printf("inner-product = %f\n", prod);
    printf("time elapsed = %f\n", t.toc());

    printf("%f GB/s\n", repeat * 2 * n * sizeof(double) / 1e9 / t.toc());
    printf("%f Gflop/s\n", repeat * 2 * n / 1e9 / t.toc());
  }

  free(x);
  free(y);

  MPI_Finalize();
  return 0;
}
