cmake_minimum_required(VERSION 3.14)

project(parallel-cpp-linalg)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -pedantic -Werror -flto=thin -O2)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "build")

add_subdirectory(tests)
# add_subdirectory(benchmarks)
add_subdirectory(src)
