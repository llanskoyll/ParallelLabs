#pragma once

#include <omp.h>
#include <utility>
#include <vector>

namespace types {
using type = float;
template <typename T> using matrix = std::vector<std::vector<T>>;
template <typename T> using vector = std::vector<T>;
} // namespace types

void gen_data(types::matrix<types::type> &matrix) {
  std::srand(std::time(nullptr));
  auto size = matrix.size();

  for (auto i = 0; i < size; ++i) {
    auto row_sum = 0;

    for (auto j = 0; j < size; ++j) {
      if (i != j) {
        matrix[i][j] = (rand() % 10) + 1;
        row_sum += matrix[i][j];
      }
    }

    matrix[i][i] = row_sum + (rand() % 5) + 1;
  }
}

types::vector<types::type> solve_gauss(types::matrix<types::type> &A,
                                       types::vector<types::type> &b) {
  int size = A.size();
  types::vector<types::type> result(size, 0.0);

  if (b.size() != size) {
    throw std::invalid_argument("Len of A and b is not equal");
  }

  for (auto i = 0; i < size; ++i) {
    auto max_row = i;
    for (auto k = i + 1; k < size; ++k) {
      if (std::fabs(A[k][i]) > std::fabs(A[max_row][i])) {
        max_row = k;
      }
    }

    if (A[max_row][i] == 0.0) {
      throw std::invalid_argument("Matrix is singular");
    }

    std::swap(A[i], A[max_row]);
    std::swap(b[i], b[max_row]);

    for (auto k = i + 1; k < size; ++k) {
      auto factor = A[k][i] / A[i][i];
      for (auto j = i; j < size; ++j) {
        A[k][j] -= factor * A[i][j];
      }
      b[k] -= factor * b[i];
    }
  }

  for (auto i = size - 1; i >= 0; --i) {
    result[i] = b[i];
    for (auto j = i + 1; j < size; ++j) {
      result[i] -= A[i][j] * result[j];
    }
    result[i] /= A[i][i];
  }

  return result;
}

types::vector<types::type> perf_solve_gauss(types::matrix<types::type> &A,
                                            types::vector<types::type> &b) {
  int size = A.size();
  types::vector<types::type> result(size, 0.0);
  if (b.size() != size) {
    throw std::invalid_argument("Len of A and b is not equal");
  }

  for (auto i = 0; i < size; ++i) {
    auto max_row = i;
    for (auto k = i + 1; k < size; ++k) {
      if (std::fabs(A[k][i]) > std::fabs(A[max_row][i])) {
        max_row = k;
      }
    }

    if (A[max_row][i] == 0.0) {
      throw std::invalid_argument("Matrix is singular");
    }

    std::swap(A[i], A[max_row]);
    std::swap(b[i], b[max_row]);

    #pragma omp parallel for
    for (auto k = i + 1; k < size; ++k) {
      auto factor = A[k][i] / A[i][i];
      for (auto j = i; j < size; ++j) {
        A[k][j] -= factor * A[i][j];
      }
      b[k] -= factor * b[i];
    }
  }

  for (auto i = size - 1; i >= 0; --i) {
    result[i] = b[i];
    for (auto j = i + 1; j < size; ++j) {
      result[i] -= A[i][j] * result[j];
    }
    result[i] /= A[i][i];
  }

  return result;
}
