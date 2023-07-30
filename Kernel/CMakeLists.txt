cmake_minimum_required(VERSION 3.20)

# C++ version
set(CMAKE_CXX_STANDARD 20)

# Set up Linker script and linker flags
set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/linker_script.ld")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostdlib -lgcc -T ${LINKER_SCRIPT}")

# Create executable with given source files
add_library(crti_obj OBJECT Architecture/i686/crti.asm)
add_library(crtn_obj OBJECT Architecture/i686/crtn.asm)

add_executable(PallaxKernel Architecture/i686/bootstrap.asm kmain.cpp multiboot.h Devices/Terminal.cpp Devices/Terminal.h Devices/VGA.h Devices/VGATerminal.cpp Devices/VGATerminal.h Devices/DeviceManager.cpp Devices/DeviceManager.h kstdio.h kstdio.cpp Devices/SerialPort.cpp Devices/SerialPort.h Architecture/i686/io.cpp Devices/io.h)
target_link_libraries(PallaxKernel PalLib)
add_dependencies(PallaxKernel crti_obj crtn_obj)

# Set the root of the Kernel source folder as an in cude directory
target_include_directories(PallaxKernel PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

# Add a dependency from the linker script to the executable
set_target_properties(PallaxKernel PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})

add_custom_command(TARGET PallaxKernel
        PRE_LINK
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_OBJECTS:crti_obj> ${CMAKE_BINARY_DIR}/crtx/crti.o
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_OBJECTS:crtn_obj> ${CMAKE_BINARY_DIR}/crtx/crtn.o
        COMMAND_EXPAND_LISTS)