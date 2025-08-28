#include <fmt/core.h>
#include <mpi.h>

#include <cstdlib>
#include <iostream>
#include <string_view>

template <typename... Args>
void error_handling(int err, std::string_view format, Args &&...args) {
  if (err != MPI_SUCCESS) {
    fmt::print(stderr, fmt::runtime(format), std::forward<Args>(args)...);
    MPI_Abort(MPI_COMM_WORLD, 1);
    std::exit(1);
  }
}

int main(int argc, char *argv[]) {
  int mpi_error = MPI_Init(&argc, &argv);
  error_handling(mpi_error, "Error MPI init with code: {}", mpi_error);

  int rank = 0;
  mpi_error = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  error_handling(mpi_error, "Error get comm rank");

  if (rank == 0) {
    fmt::print("Root process: Hello, world!\n");
  } else {
    fmt::print("Slave process: my rank is {}\n", rank);
  }

  MPI_Finalize();

  return 0;
}
