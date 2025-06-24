
project(EigenAOCLBench)

add_executable(benchmark_aocl benchmark_aocl.cpp)

# Use C++11 and apply common flags similar to the standalone Makefile
target_compile_features(benchmark_aocl PRIVATE cxx_std_11)
target_compile_options(benchmark_aocl PRIVATE -std=c++11 -O3 -g -Wno-parentheses)

# Enable AOCL usage for this benchmark
target_compile_definitions(benchmark_aocl PRIVATE EIGEN_USE_AOCL_ALL)

# Add AOCL include directory if provided
if(AOCL_ROOT)
  target_include_directories(benchmark_aocl PRIVATE ${AOCL_ROOT}/include)
endif()

if(EIGEN_STANDARD_LIBRARIES_TO_LINK_TO)
  target_link_libraries(benchmark_aocl ${EIGEN_STANDARD_LIBRARIES_TO_LINK_TO})
endif()


if(AOCL_LIBRARIES)
  target_link_libraries(benchmark_aocl ${AOCL_LIBRARIES})
endif()