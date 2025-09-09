#include <fmt/core.h>

#include <benchmark/benchmark.h>

#include "include/bench.hpp"
#include "include/test.hpp"

// ./app --benchmark_format=json --benchmark_out=stats.json
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
