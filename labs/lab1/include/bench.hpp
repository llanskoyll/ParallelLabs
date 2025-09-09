#pragma once

#include <benchmark/benchmark.h>
#include <functional>

#include "matrix_mul.hpp"

void register_bench_with_files(std::string test_case,
                               std::function<void(benchmark::State &)> func,
                               uint64_t step = 32, int64_t max = 8196) {
  for (auto i = 0U; i <= max; i += step) {
    ::benchmark::RegisterBenchmark(test_case.c_str(), func)->Arg(i);
  }
}

void BM_Matrix(benchmark::State &state) {
  auto size = state.range(0);
  std::vector<std::vector<int>> matrix_a(size, std::vector<int>(size));
  std::vector<std::vector<int>> matrix_b(size, std::vector<int>(size));
  std::vector<std::vector<int>> result(size, std::vector<int>(size, 0));

  for (auto _ : state) {
    matrix_mull(matrix_a, matrix_b, result);
  }

  state.SetLabel("BASE_MATRIX_" + std::to_string(size));
}

void BM_MatrixThread(benchmark::State &state) {
  auto size = state.range(0);
  std::vector<std::vector<int>> matrix_a(size, std::vector<int>(size));
  std::vector<std::vector<int>> matrix_b(size, std::vector<int>(size));
  std::vector<std::vector<int>> result(size, std::vector<int>(size, 0));

  for (auto _ : state) {
    matrix_mull_perf(matrix_a, matrix_b, result);
  }
  state.SetLabel("THREAD_MATRIX_" + std::to_string(size));
}

void register_bench() {
  register_bench_with_files("BM_Matrix", &BM_Matrix, 32, 2048);
  register_bench_with_files("BM_MatrixThread", &BM_MatrixThread, 32, 2048);
}