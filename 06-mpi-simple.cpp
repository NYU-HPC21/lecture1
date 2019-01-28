// $ mpic++ 06-mpi-simple.cpp && mpirun -n 4 ./a.out

#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);
  MPI_Comm comm = MPI_COMM_WORLD;

  int mpirank, mpisize;
  MPI_Comm_rank(comm, &mpirank);
  MPI_Comm_size(comm, &mpisize);

  printf("I am process %d of %d\n", mpirank, mpisize);

  MPI_Finalize();
  return 0;
}
