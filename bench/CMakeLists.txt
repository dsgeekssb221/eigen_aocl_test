project(EigenAOCLBench)

add_executable(benchmark_aocl benchmark_aocl.cpp)

if(EIGEN_STANDARD_LIBRARIES_TO_LINK_TO)
  target_link_libraries(benchmark_aocl ${EIGEN_STANDARD_LIBRARIES_TO_LINK_TO})
endif()

