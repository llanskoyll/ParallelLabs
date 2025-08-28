cmake_minimum_required(VERSION 3.16)
project(app LANGUAGES C CXX)

find_package(MPI REQUIRED)
find_package(OpenMP REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE MPI::MPI_CXX OpenMP::OpenMP_CXX)
