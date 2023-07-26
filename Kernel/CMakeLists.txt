cmake_minimum_required(VERSION 3.20)

# C++ version
set(CMAKE_CXX_STANDARD 20)


# C and C++ compiler flags

# TODO: Change the -O2 flag depending on debug level
set(PALLAX_C_FLAGS "-O2 -ffreestanding -Wall -Wextra")
set(PALLAX_CXX_FLAGS "${PALLAX_C_FLAGS} -fno-exceptions -fno-rtti")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${PALLAX_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PALLAX_CXX_FLAGS}")

# Set up Linker script and linker flags
set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/linker_script.ld")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostdlib -lgcc -T ${LINKER_SCRIPT}")

# Create executable with given source files
add_executable(PallaxKernel Architecture/i686/bootstrap.asm main.cpp)

# Add a dependency from the linker script to the executable
set_target_properties(PallaxKernel PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})