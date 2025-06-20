/*
 * AOCL_support.h - AOCL-specific support definitions for Eigen
 *
 * Copyright (c) 2025, Advanced Micro Devices, Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *   * Neither the name of Advanced Micro Devices, Inc. nor the names of its contributors
 *     may be used to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Description:
 * ------------
 * This header enables AOCL integration for Eigen, including Vector Math Library (VML),
 * BLAS (libblis), and LAPACK (libflame). It defines necessary macros when
 * EIGEN_USE_AOCL_ALL is set, ensuring Eigen uses AOCL’s optimized libraries.
 * This file is independently developed, inspired by common Eigen integration patterns,
 * and contains no proprietary code from other vendors (e.g., Intel MKL).
 *
 * Usage:
 * ------
 * Include this header BEFORE any Eigen headers. Compile with -DEIGEN_USE_AOCL_ALL.
 * Link with -lamdlibm -lblis -lflame.
 * 
 * Developer:
 * ----------
 * Name: Sharad Saurabh Bhaskar
 * Email: shbhaska@amd.com
 */

 #ifndef EIGEN_AOCL_SUPPORT_H
 #define EIGEN_AOCL_SUPPORT_H
 
 #include <complex>  // For std::complex
 
 #ifdef EIGEN_USE_AOCL_ALL
   // Enable AOCL Vector Math Library (VML)
   #define EIGEN_USE_AOCL_VML
 
   // Enable AOCL BLAS and LAPACK with Eigen-standard macros
   #define EIGEN_USE_BLAS     // Routes to libblis (e.g., bli_dgemm)
   #define EIGEN_USE_LAPACKE  // Routes to libflame (e.g., dsyev via LAPACKE)
 
  // Include AOCL VML header
  #include "amdlibm.h"

  // Enable experimental vector interfaces
  #ifndef AMD_LIBM_VEC_EXPERIMENTAL
    #define AMD_LIBM_VEC_EXPERIMENTAL
  #endif
  #include "amdlibm_vec.h"
 #endif
 
 // Handle strict LAPACKE usage
 #ifdef EIGEN_USE_LAPACKE_STRICT
   #define EIGEN_USE_LAPACKE
 #endif
 
 // Define AOCL flag for VML usage
 #if defined(EIGEN_USE_AOCL_VML) && !defined(EIGEN_USE_AOCL)
   #define EIGEN_USE_AOCL
 #endif
 
 // Configuration constants
 #ifndef EIGEN_AOCL_VML_THRESHOLD
   #define EIGEN_AOCL_VML_THRESHOLD 128  // Threshold for VML dispatch
 #endif
 
 #ifndef AOCL_SIMD_WIDTH
   #define AOCL_SIMD_WIDTH 8             // AVX-512: 512 bits / 64 bits per double
 #endif
 
 namespace Eigen {
   typedef std::complex<double> dcomplex;
   typedef std::complex<float>  scomplex;
   typedef int BlasIndex;  // Standard BLAS index type
 }
 
 #endif // EIGEN_AOCL_SUPPORT_H
