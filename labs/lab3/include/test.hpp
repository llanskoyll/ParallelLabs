#pragma once

#include <cmath>
#include <gtest/gtest.h>

#include <cmath>
#include <cstdlib>
#include <ctime>

#include "integral.hpp"
#include <fmt/core.h>

TEST(Integral, BaseOne) {
  // f(x) = sin(x) * cos(x) + sqrt(x)
  auto fun = [](double x) { return std::sin(x) * std::cos(x) + std::sqrt(x); };

  auto result = integral::integrate(10, 20, 0.0001, fun);
  auto golden_result = 38.8153;
  EXPECT_NEAR(result, golden_result, 1);
}

TEST(Integral, BaseTwo) {
  // f(x) = x^2 * sin(x)
  auto fun = [](double x) { return std::pow(x, 2) * std::sin(x); };

  auto result = integral::integrate(10, 20, 0.01, fun);
  auto golden_result = -197.8589;
  EXPECT_NEAR(result, golden_result, 1);
}

TEST(Integral, PerfOne) {
  // f(x) = sin(x) * cos(x) + sqrt(x)
  auto fun = [](double x) { return std::sin(x) * std::cos(x) + std::sqrt(x); };

  auto result = integral::perf_integrate(10, 20, 0.0001, fun);
  auto golden_result = 38.8153;
  EXPECT_NEAR(result, golden_result, 1);
}

TEST(Integral, Perftwo) {
  // f(x) = x^2 * sin(x)
  auto fun = [](double x) { return std::pow(x, 2) * std::sin(x); };

  auto result = integral::perf_integrate(10, 20, 0.01, fun);
  auto golden_result = -197.8589;
  EXPECT_NEAR(result, golden_result, 1);
}
