#include "test.hpp"
#include "bench.hpp"
#include <benchmark/benchmark.h>

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest();
  if (RUN_ALL_TESTS() != 0) {
    exit(1);
  }

  ::benchmark::Initialize(&argc, argv);
  register_bench();
  ::benchmark::RunSpecifiedBenchmarks();

  return 0;
}