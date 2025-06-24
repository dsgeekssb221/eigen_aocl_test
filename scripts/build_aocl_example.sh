#!/bin/bash
# Build AOCL-enabled Eigen and run the benchmark
# Usage: ./build_aocl_example.sh [extra-cmake-options]
# Requires AOCL_ROOT to be set to the AOCL installation path.

set -e

EIGEN_REPO_URL=${EIGEN_REPO_URL:-"https://gitlab.com/libeigen/eigen.git"}
EIGEN_DIR="eigen_aocl"

if [ ! -d "$EIGEN_DIR" ]; then
  git clone "$EIGEN_REPO_URL" "$EIGEN_DIR"
fi

cd "$EIGEN_DIR"

mkdir -p build
cd build

cmake .. -DEIGEN_BUILD_AOCL_BENCH=ON \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_C_COMPILER=clang \
  -DCMAKE_CXX_COMPILER=clang++ \
  -DCMAKE_INSTALL_PREFIX="${PWD}/install" \
  -DINCLUDE_INSTALL_DIR="${PWD}/install/include" \
  -DEIGEN_USE_AOCL_ALL=ON "$@"

make -j$(nproc) benchmark_aocl

make install
make doc || echo "Documentation generation failed"

./bench/benchmark_aocl || echo "Benchmark execution failed"
