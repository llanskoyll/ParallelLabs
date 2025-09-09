#pragma once

#include <vector>

#include <omp.h>

void gen_data(std::vector<std::vector<int>> &matrix) {
  for (auto &row : matrix) {
    for (auto &elem : row) {
      elem = (rand() % 10) + 1;
    }
  }
}

void matrix_mull(const std::vector<std::vector<int>> &A,
                 const std::vector<std::vector<int>> &B,
                 std::vector<std::vector<int>> &C) {
  auto n = A.size();
  for (auto i = 0U; i < n; ++i) {
    for (auto j = 0U; j < n; ++j) {
      for (auto k = 0U; k < n; ++k) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}

void matrix_mull_perf(const std::vector<std::vector<int>> &A,
                      const std::vector<std::vector<int>> &B,
                      std::vector<std::vector<int>> &C) {
  auto n = A.size();
#pragma omp parallel for
  for (auto i = 0U; i < n; ++i) {
    for (auto j = 0U; j < n; ++j) {
      int sum = 0;
#pragma omp simd reduction(+ : sum)
      for (auto k = 0U; k < n; ++k) {
        sum += A[i][k] * B[k][j];
      }
      C[i][j] = sum;
    }
  }
}