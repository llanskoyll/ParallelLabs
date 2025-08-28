cmake_minimum_required(VERSION 3.16)
project(app)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(MPI REQUIRED)
find_package(OpenMP REQUIRED)
find_package(fmt REQUIRED)

add_executable(task1 task1.cpp)
add_executable(task2 task2.cpp)

target_link_libraries(task1 PRIVATE MPI::MPI_CXX OpenMP::OpenMP_CXX fmt::fmt)
target_link_libraries(task2 PRIVATE MPI::MPI_CXX OpenMP::OpenMP_CXX fmt::fmt)
