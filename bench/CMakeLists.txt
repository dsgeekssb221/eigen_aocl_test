project(EigenAOCLBench)

add_executable(benchmark_aocl benchmark_aocl.cpp)

target_compile_features(benchmark_aocl PRIVATE cxx_std_11)
target_compile_options(benchmark_aocl PRIVATE -std=c++11)


if(EIGEN_STANDARD_LIBRARIES_TO_LINK_TO)
  target_link_libraries(benchmark_aocl ${EIGEN_STANDARD_LIBRARIES_TO_LINK_TO})
endif()

