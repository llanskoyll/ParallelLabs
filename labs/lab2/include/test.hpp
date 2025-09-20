#pragma once

#include <Eigen/Dense>
#include <cmath>
#include <gtest/gtest.h>

#include <cstdlib>
#include <ctime>

#include "solve_eq.hpp"
#include <fmt/core.h>

class SolveEqParamTest : public ::testing::TestWithParam<int> {};

TEST(Core, CheckEigen) {
  Eigen::Matrix3f A;
  Eigen::Vector3f b;
  Eigen::Vector3f x;

  //  2x + y - 1z = 8
  // -3x - y + 2z = -11
  // -2x + y + 2z = -3
  A << 2, 1, -1, -3, -1, 2, -2, 1, 2;
  b << 8, -11, -3;
  // .lu().solve() - classic method of solving eq by Gaus
  x = A.lu().solve(b);

  EXPECT_EQ(static_cast<int>(std::round(x[0])), 2);
  EXPECT_EQ(static_cast<int>(std::round(x[1])), 3);
  EXPECT_EQ(static_cast<int>(std::round(x[2])), -1);
}

TEST_P(SolveEqParamTest, SolveGauss) {
  int size = GetParam();

  types::matrix<types::type> A(size, types::vector<types::type>(size));
  gen_data(A);
  types::vector<types::type> B(size);
  for (int i = 0; i < size; ++i) {
    B[i] = rand() % 10 + 1;
  }

  types::vector<types::type> result = solve_gauss(A, B);

  Eigen::MatrixXd golden_A(size, size);
  Eigen::VectorXd golden_B(size);
  for (int i = 0; i < size; ++i) {
    golden_B(i) = B[i];
    for (int j = 0; j < size; ++j) {
      golden_A(i, j) = A[i][j];
    }
  }
  Eigen::VectorXd golden_result = golden_A.lu().solve(golden_B);

  for (int i = 0; i < size; ++i) {
    EXPECT_NEAR(result[i], golden_result(i), 1e-6);
  }
}

TEST_P(SolveEqParamTest, PerfSolveGauss) {
  int size = GetParam();

  types::matrix<types::type> A(size, types::vector<types::type>(size));
  gen_data(A);
  types::vector<types::type> B(size);
  for (int i = 0; i < size; ++i) {
    B[i] = rand() % 10 + 1;
  }

  types::vector<types::type> result = perf_solve_gauss(A, B);

  Eigen::MatrixXd golden_A(size, size);
  Eigen::VectorXd golden_B(size);
  for (int i = 0; i < size; ++i) {
    golden_B(i) = B[i];
    for (int j = 0; j < size; ++j) {
      golden_A(i, j) = A[i][j];
    }
  }
  Eigen::VectorXd golden_result = golden_A.lu().solve(golden_B);

  for (int i = 0; i < size; ++i) {
    EXPECT_NEAR(result[i], golden_result(i), 1e-6);
  }
}

INSTANTIATE_TEST_SUITE_P(SolveEq, SolveEqParamTest, ::testing::Range(4, 10, 1));
