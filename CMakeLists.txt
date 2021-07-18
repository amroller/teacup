# MIT License
#
# Copyright (c) 2021 Aaron M. Roller
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# ==============================================================================
# Project configuration

cmake_minimum_required(VERSION 3.12)
project(Teacup LANGUAGES CXX)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to \"Release\" as none was specified")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

# ==============================================================================
# Collect source files

set(TEACUP_SOURCE
    "source/teacup/maths.h"
    "source/teacup/maths.cc"
    "source/teacup/teacup.cc"
    "source/teacup/types.h"
)

set(TESTS_SOURCE
    "source/teacup/maths.cc"
    "source/tests/maths.cc"
    "source/tests/tests.cc"
)

# ==============================================================================
# Define teacup

add_executable(teacup
    ${TEACUP_SOURCE}
)

target_include_directories(teacup PRIVATE
    "source/"
    "source/extern/"
)

# ==============================================================================
# Define tests

add_executable(tests
    ${TESTS_SOURCE}
)

target_include_directories(tests PRIVATE
    "source/"
    "source/extern/"
)

add_test(tests tests)

# ==============================================================================
# IDE support

set_directory_properties(PROPERTIES VS_STARTUP_PROJECT teacup)
source_group(teacup FILES ${TEACUP_SOURCE})
source_group(tests FILES ${TESTS_SOURCE})
