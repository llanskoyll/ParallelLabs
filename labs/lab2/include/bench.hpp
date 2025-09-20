
#pragma once

#include <benchmark/benchmark.h>
#include <functional>

#include "solve_eq.hpp"
#include "test.hpp"

void register_bench_with_files(std::string test_case,
                               std::function<void(benchmark::State &)> func,
                               uint64_t start = 0, int64_t max = 8196,
                               uint64_t step = 32) {
  for (auto i = start; i <= max; i += step) {
    ::benchmark::RegisterBenchmark(test_case.c_str(), func)->Arg(i);
  }
}

void BM_SolveGauss(benchmark::State &state) {
  auto size = state.range(0);

  types::matrix<types::type> A(size, types::vector<types::type>(size));
  gen_data(A);
  types::vector<types::type> B(size);
  for (int i = 0; i < size; ++i) {
    B[i] = rand() % 10 + 1;
  }

  gen_data(A);
  for (auto _ : state) {
    solve_gauss(A, B);
  }

  state.SetLabel("BASE_SOLVE_GAUSS_" + std::to_string(size));
}

void BM_PerfSolveGauss(benchmark::State &state) {
  auto size = state.range(0);

  types::matrix<types::type> A(size, types::vector<types::type>(size));
  gen_data(A);
  types::vector<types::type> B(size);
  for (int i = 0; i < size; ++i) {
    B[i] = rand() % 10 + 1;
  }

  gen_data(A);
  for (auto _ : state) {
    perf_solve_gauss(A, B);
  }

  state.SetLabel("PERF_SOLVE_GAUSS_" + std::to_string(size));
}

void register_bench() {
  register_bench_with_files("BM_PerfSolveGauss", &BM_PerfSolveGauss, 50, 3000,
                            50);
  register_bench_with_files("BM_SolveGauss", &BM_SolveGauss, 50, 3000, 50);
}