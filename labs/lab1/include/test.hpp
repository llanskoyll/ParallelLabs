#pragma once

#include <Eigen/Dense>
#include <cmath>
#include <gtest/gtest.h>

#include "matrix_mul.hpp"

class MatrixParamTest : public ::testing::TestWithParam<int> {};

TEST(Core, CheckEigen) {
  std::vector<std::vector<int>> matrix_a{{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
  std::vector<std::vector<int>> matrix_b{{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
  std::vector<std::vector<int>> result{{6, 12, 18}, {6, 12, 18}, {6, 12, 18}};

  int n = matrix_a.size();
  Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> A(n, n);
  Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> B(n, n);
  Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> R(n, n);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      A(i, j) = matrix_a[i][j];
      B(i, j) = matrix_b[i][j];
      R(i, j) = result[i][j];
    }
  }

  Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> C = A * B;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      ASSERT_EQ(C(i, j), R(i, j));
    }
  }

  ASSERT_EQ(C.rows(), n);
  ASSERT_EQ(C.cols(), n);
}

TEST_P(MatrixParamTest, Based) {
  int size = MatrixParamTest::GetParam();
  fmt::print("Size of Matrix {}\n", size);

  std::vector<std::vector<int>> matrix_a(size, std::vector<int>(size));
  std::vector<std::vector<int>> matrix_b(size, std::vector<int>(size));
  gen_data(matrix_a);
  gen_data(matrix_b);

  Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> matrix_A(size, size);
  Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> matrix_B(size, size);
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      matrix_A(i, j) = matrix_a[i][j];
      matrix_B(i, j) = matrix_b[i][j];
    }
  }

  Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> golden_result =
      matrix_A * matrix_B;
  std::vector<std::vector<int>> result(size, std::vector<int>(size, 0));

  matrix_mull(matrix_a, matrix_b, result);

  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      ASSERT_EQ(golden_result(i, j), result[i][j]);
    }
  }
}

TEST_P(MatrixParamTest, MultiThreading) {
  int size = MatrixParamTest::GetParam();
  fmt::print("Size of Matrix {}\n", size);

  std::vector<std::vector<int>> matrix_a(size, std::vector<int>(size));
  std::vector<std::vector<int>> matrix_b(size, std::vector<int>(size));
  gen_data(matrix_a);
  gen_data(matrix_b);

  Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> matrix_A(size, size);
  Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> matrix_B(size, size);
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      matrix_A(i, j) = matrix_a[i][j];
      matrix_B(i, j) = matrix_b[i][j];
    }
  }

  Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> golden_result =
      matrix_A * matrix_B;
  std::vector<std::vector<int>> result(size, std::vector<int>(size, 0));

  matrix_mull_perf(matrix_a, matrix_b, result);

  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      ASSERT_EQ(golden_result(i, j), result[i][j]);
    }
  }
}

INSTANTIATE_TEST_SUITE_P(MatrixParam, MatrixParamTest,
                         ::testing::Range(256, 1024, 256));
