# - Try to find how to link to the standard math library, if anything at all is needed to do.
# On most platforms this is automatic, but for example it's not automatic on QNX.
#
# Once done this will define
#
#  STANDARD_MATH_LIBRARY_FOUND - we found how to successfully link to the standard math library
#  STANDARD_MATH_LIBRARY - the name of the standard library that one has to link to.
#                            -- this will be left empty if it's automatic (most platforms).
#                            -- this will be set to "m" on platforms where one must explicitly
#                               pass the "-lm" linker flag.
#
# Copyright (c) 2010 Benoit Jacob <jacob.benoit.1@gmail.com>
# Redistribution and use is allowed according to the terms of the 2-clause BSD license.


include(CheckCXXSourceCompiles)
set(find_standard_math_library_test_program
"#include <cmath>
int main() { std::sin(0.0); std::log(0.0f); return 0; }")

# --- Begin AOCL MathLib Section ---
if(DEFINED EIGEN_USE_AOCL_ALL AND EIGEN_USE_AOCL_ALL)
  set(STANDARD_MATH_LIBRARY "amdlibm;m")
  set(STANDARD_MATH_LIBRARY_FOUND TRUE)
  message(STATUS "AOCL MathLib enabled; linking with -lamdlibm -lm.")
  message(STATUS "For fast math mode, preload via LD_PRELOAD=/path/to/libalmfast.so")
endif()
# --- End AOCL MathLib Section ---

if(NOT STANDARD_MATH_LIBRARY_FOUND)
  # We have to check whether the standard math library is linked automatically or not.
  # This is the case on most platforms, but not on QNX for example.
  # The test program below will try to use some functions from the standard math library,
  # and if it compiles and links successfully, then we know that the standard math library
  # is linked automatically.

  set(CMAKE_REQUIRED_FLAGS "-std=c++11")
  set(CMAKE_REQUIRED_LIBRARIES "")
  CHECK_CXX_SOURCE_COMPILES(
    "${find_standard_math_library_test_program}"
    standard_math_library_linked_to_automatically
)

if(standard_math_library_linked_to_automatically)

  # the test program linked successfully without any linker flag.
  set(STANDARD_MATH_LIBRARY "")
  set(STANDARD_MATH_LIBRARY_FOUND TRUE)

else()

  # the test program did not link successfully without any linker flag.
  # This is a very uncommon case that so far we only saw on QNX. The next try is the
  # standard name 'm' for the standard math library.

  set(CMAKE_REQUIRED_LIBRARIES "m")
  CHECK_CXX_SOURCE_COMPILES(
    "${find_standard_math_library_test_program}"
    standard_math_library_linked_to_as_m)

  if(standard_math_library_linked_to_as_m)

    # the test program linked successfully when linking to the 'm' library
    set(STANDARD_MATH_LIBRARY "m")
    set(STANDARD_MATH_LIBRARY_FOUND TRUE)

  else()

    # the test program still doesn't link successfully
    set(STANDARD_MATH_LIBRARY_FOUND FALSE)

  endif()

endif()
endif()

