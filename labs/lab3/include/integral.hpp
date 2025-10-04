#pragma once

#include <chrono>
#include <functional>
#include <omp.h>
#include <random>
#include <stdexcept>
#include <vector>

namespace integral {

auto integrate(double from, double to, double step,
               std::function<double(double)> func) {
  if (from >= to)
    throw std::invalid_argument("From must be less than to");
  if (step <= 0)
    throw std::invalid_argument("Step must be > 0");

  auto result = 0.0;
  auto current = from;

  while (current + step <= to) {
    result += (func(current) + func(current + step)) * 0.5 * step;
    current += step;
  }

  if (current < to) {
    auto last_step = to - current;
    result += (func(current) + func(to)) * 0.5 * last_step;
  }

  return result;
}

auto perf_integrate(double from, double to, double step,
                    std::function<double(double)> func) {
  if (from >= to)
    throw std::invalid_argument("From must be less than to");
  if (step <= 0)
    throw std::invalid_argument("Step must be > 0");

  auto num_intervals = static_cast<long long>((to - from) / step);
  auto result = .0;

#pragma omp parallel
  {
    auto local_sum = 0.0;

#pragma omp for nowait
    for (auto i = 0ULL; i < num_intervals; ++i) {
      auto x0 = from + i * step;
      auto x1 = x0 + step;
      local_sum += (func(x0) + func(x1)) * 0.5 * step;
    }

#pragma omp atomic
    result += local_sum;
  }

  auto last_x = from + num_intervals * step;
  if (last_x < to) {
    auto last_step = to - last_x;
    result += (func(last_x) + func(to)) * 0.5 * last_step;
  }

  return result;
}

} // namespace integral
