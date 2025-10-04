
#pragma once

#include <benchmark/benchmark.h>
#include <cmath>
#include <functional>

#include "integral.hpp"
#include "test.hpp"

void register_bench_with_files(std::string test_case,
                               std::function<void(benchmark::State &)> func) {
  ::benchmark::RegisterBenchmark((test_case + "_1e-1").c_str(), func)->Arg(1);
  ::benchmark::RegisterBenchmark((test_case + "_1e-2").c_str(), func)->Arg(2);
  ::benchmark::RegisterBenchmark((test_case + "_1e-3").c_str(), func)->Arg(3);
  ::benchmark::RegisterBenchmark((test_case + "_1e-4").c_str(), func)->Arg(4);
  ::benchmark::RegisterBenchmark((test_case + "_1e-5").c_str(), func)->Arg(5);
  ::benchmark::RegisterBenchmark((test_case + "_1e-6").c_str(), func)->Arg(6);
}

void BM_Integral(benchmark::State &state) {
  auto precision = state.range(0);
  double step = std::pow(10, -precision);

  auto fun = [](double x) { return std::sin(x) * std::cos(x) + std::sqrt(x); };

  for (auto _ : state) {
    auto result = integral::integrate(1, 1000, step, fun);
    benchmark::DoNotOptimize(result);
  }

  state.SetLabel("BASE_INTEGRAL_step_1e-" + std::to_string(precision));
}

void BM_IntegralParallel(benchmark::State &state) {
  auto precision = state.range(0);
  double step = std::pow(10, -precision);

  auto fun = [](double x) { return std::sin(x) * std::cos(x) + std::sqrt(x); };

  for (auto _ : state) {
    auto result = integral::perf_integrate(1, 1000, step, fun);
    benchmark::DoNotOptimize(result);
  }

  state.SetLabel("PARALLEL_INTEGRAL_step_1e-" + std::to_string(precision));
}

void register_bench() {
  register_bench_with_files("BM_Integral", &BM_Integral);
  register_bench_with_files("BM_IntegralParallel", &BM_IntegralParallel);
}