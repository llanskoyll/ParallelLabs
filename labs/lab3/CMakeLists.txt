cmake_minimum_required(VERSION 3.16)
project(app)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenMP REQUIRED)
find_package(fmt REQUIRED)
find_package(benchmark REQUIRED)
find_package(GTest REQUIRED)
find_package(Eigen3 REQUIRED NO_MODULE)


add_executable(${PROJECT_NAME} main.cpp)

include_directories(${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    OpenMP::OpenMP_CXX
    fmt::fmt
    benchmark::benchmark
    GTest::GTest
    GTest::Main
    pthread
    Eigen3::Eigen
)
