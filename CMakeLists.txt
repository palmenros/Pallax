cmake_minimum_required(VERSION 3.20)

# Don't try to check cross-compiler with an executable, as that will fail
# Instead, try to compile a static library.
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(Pallax C CXX ASM)

# Verify that the correct cross-compiling toolchain is being used
if(NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Generic")
    message(FATAL_ERROR "System name is '${CMAKE_SYSTEM_NAME}', which isn't 'Generic'."
    " You are not using the correct cross-compiling toolchain.")
endif ()

# Compile kernel
add_subdirectory(Kernel)