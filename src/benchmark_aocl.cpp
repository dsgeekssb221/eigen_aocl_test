#include <iostream>
#include <chrono>
#include <vector>

#ifdef EIGEN_USE_MKL_ALL
  #include <Eigen/Core>
  #include "Eigen/src/Core/util/MKL_support.h"
  #include "Eigen/src/Core/Assign_MKL.h"
#endif

#ifdef EIGEN_USE_AOCL_ALL
  #include "Eigen/src/Core/AOCL_Support.h"
  #include "Eigen/src/Core/Assign_AOCL.h"
#endif

#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

using namespace std;
using namespace std::chrono;
using namespace Eigen;

void benchmarkVectorMath(int size) {
    VectorXd v = VectorXd::LinSpaced(size, 0.1, 10.0);
    VectorXd result(size);
    double elapsed_ms = 0;

    cout << "\n--- Vector Math Benchmark (size = " << size << ") ---" << endl;

    auto start = high_resolution_clock::now();
    result = v.array().exp();
    auto end = high_resolution_clock::now();
    elapsed_ms = duration_cast<milliseconds>(end - start).count();
    cout << "exp() time: " << elapsed_ms << " ms" << endl;

    start = high_resolution_clock::now();
    result = v.array().sin();
    end = high_resolution_clock::now();
    elapsed_ms = duration_cast<milliseconds>(end - start).count();
    cout << "sin() time: " << elapsed_ms << " ms" << endl;

    start = high_resolution_clock::now();
    result = v.array().cos();
    end = high_resolution_clock::now();
    elapsed_ms = duration_cast<milliseconds>(end - start).count();
    cout << "cos() time: " << elapsed_ms << " ms" << endl;

    start = high_resolution_clock::now();
    result = v.array().sqrt();
    end = high_resolution_clock::now();
    elapsed_ms = duration_cast<milliseconds>(end - start).count();
    cout << "sqrt() time: " << elapsed_ms << " ms" << endl;

    start = high_resolution_clock::now();
    result = v.array().log();
    end = high_resolution_clock::now();
    elapsed_ms = duration_cast<milliseconds>(end - start).count();
    cout << "log() time: " << elapsed_ms << " ms" << endl;

    start = high_resolution_clock::now();
    result = v.array().log10();
    end = high_resolution_clock::now();
    elapsed_ms = duration_cast<milliseconds>(end - start).count();
    cout << "log10() time: " << elapsed_ms << " ms" << endl;

    start = high_resolution_clock::now();
    result = v.array().asin();
    end = high_resolution_clock::now();
    elapsed_ms = duration_cast<milliseconds>(end - start).count();
    cout << "asin() time: " << elapsed_ms << " ms" << endl;

    start = high_resolution_clock::now();
    result = v.array().sinh();
    end = high_resolution_clock::now();
    elapsed_ms = duration_cast<milliseconds>(end - start).count();
    cout << "sinh() time: " << elapsed_ms << " ms" << endl;

    start = high_resolution_clock::now();
    result = v.array().acos();
    end = high_resolution_clock::now();
    elapsed_ms = duration_cast<milliseconds>(end - start).count();
    cout << "acos() time: " << elapsed_ms << " ms" << endl;

    start = high_resolution_clock::now();
    result = v.array().cosh();
    end = high_resolution_clock::now();
    elapsed_ms = duration_cast<milliseconds>(end - start).count();
    cout << "cosh() time: " << elapsed_ms << " ms" << endl;

    start = high_resolution_clock::now();
    result = v.array().tan();
    end = high_resolution_clock::now();
    elapsed_ms = duration_cast<milliseconds>(end - start).count();
    cout << "tan() time: " << elapsed_ms << " ms" << endl;

    start = high_resolution_clock::now();
    result = v.array().atan();
    end = high_resolution_clock::now();
    elapsed_ms = duration_cast<milliseconds>(end - start).count();
    cout << "atan() time: " << elapsed_ms << " ms" << endl;

    start = high_resolution_clock::now();
    result = v.array().tanh();
    end = high_resolution_clock::now();
    elapsed_ms = duration_cast<milliseconds>(end - start).count();
    cout << "tanh() time: " << elapsed_ms << " ms" << endl;

    VectorXd v2 = VectorXd::Random(size);
    start = high_resolution_clock::now();
    result = v.array() + v2.array();
    end = high_resolution_clock::now();
    elapsed_ms = duration_cast<milliseconds>(end - start).count();
    cout << "add() time: " << elapsed_ms << " ms" << endl;

    start = high_resolution_clock::now();
    result = v.array().pow(2.0);
    end = high_resolution_clock::now();
    elapsed_ms = duration_cast<milliseconds>(end - start).count();
    cout << "pow() time: " << elapsed_ms << " ms" << endl;
}

void benchmarkMatrixMultiplication(int matSize) {
    cout << "\n--- Matrix Multiplication Benchmark (" << matSize << " x " << matSize << ") ---" << endl;
    MatrixXd A = MatrixXd::Random(matSize, matSize);
    MatrixXd B = MatrixXd::Random(matSize, matSize);
    MatrixXd C(matSize, matSize);

    auto start = high_resolution_clock::now();
    C = A * B;
    auto end = high_resolution_clock::now();
    double elapsed_ms = duration_cast<milliseconds>(end - start).count();
    cout << "Matrix multiplication time: " << elapsed_ms << " ms" << endl;
}

void benchmarkEigenDecomposition(int matSize) {
    cout << "\n--- Eigenvalue Decomposition Benchmark (Matrix Size: " << matSize << " x " << matSize << ") ---" << endl;
    MatrixXd M = MatrixXd::Random(matSize, matSize);
    M = (M + M.transpose()) * 0.5;

    SelfAdjointEigenSolver<MatrixXd> eigensolver;
    auto start = high_resolution_clock::now();
    eigensolver.compute(M);
    auto end = high_resolution_clock::now();
    double elapsed_ms = duration_cast<milliseconds>(end - start).count();
    if (eigensolver.info() == Success) {
        cout << "Eigenvalue decomposition time: " << elapsed_ms << " ms" << endl;
    } else {
        cout << "Eigenvalue decomposition failed." << endl;
    }
}

void benchmarkFSIRiskComputation(int numPeriods, int numAssets) {
    cout << "\n--- FSI Risk Computation Benchmark ---" << endl;
    cout << "Simulating " << numPeriods << " periods for " << numAssets << " assets." << endl;

    MatrixXd returns = MatrixXd::Random(numPeriods, numAssets);

    auto start = high_resolution_clock::now();
    MatrixXd cov = (returns.transpose() * returns) / (numPeriods - 1);
    auto end = high_resolution_clock::now();
    double cov_time = duration_cast<milliseconds>(end - start).count();
    cout << "Covariance matrix computation time: " << cov_time << " ms" << endl;

    SelfAdjointEigenSolver<MatrixXd> eigensolver;
    start = high_resolution_clock::now();
    eigensolver.compute(cov);
    end = high_resolution_clock::now();
    double eig_time = duration_cast<milliseconds>(end - start).count();
    if (eigensolver.info() == Success) {
        cout << "Eigenvalue decomposition (covariance) time: " << eig_time << " ms" << endl;
        cout << "Top 3 Eigenvalues: " << eigensolver.eigenvalues().tail(3).transpose() << endl;
    } else {
        cout << "Eigenvalue decomposition failed." << endl;
    }
}

int main() {
    vector<int> vectorSizes = {100000, 1000000, 5000000, 10000000, 50000000};
    for (int size : vectorSizes) {
        benchmarkVectorMath(size);
    }

    vector<int> matrixSizes = {2048, 4096, 8192};
    for (int msize : matrixSizes) {
        benchmarkMatrixMultiplication(msize);
    }

    for (int msize : matrixSizes) {
        benchmarkEigenDecomposition(msize);
    }

    benchmarkFSIRiskComputation(10000, 500);
    return 0;
}

