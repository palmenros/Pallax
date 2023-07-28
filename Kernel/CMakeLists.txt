cmake_minimum_required(VERSION 3.20)

# C++ version
set(CMAKE_CXX_STANDARD 20)

# Set up Linker script and linker flags
set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/linker_script.ld")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostdlib -lgcc -T ${LINKER_SCRIPT}")

# Create executable with given source files

# TODO: Set first and last objects to link into kernel to support global constructors and destructors.
#  These need to be linked in an specific order that is important to maintain.
set(PALLAX_LINK_FIRST_OBJECTS inicio_dos)
set(PALLAX_LINK_LAST_OBJECTS final_dos)

add_library(crti_obj OBJECT Architecture/i686/crti.asm)
add_library(crtn_obj OBJECT Architecture/i686/crtn.asm)

add_executable(PallaxKernel Architecture/i686/bootstrap.asm main.cpp multiboot.h IO/Terminal.cpp IO/Terminal.h IO/VGA.h)
target_link_libraries(PallaxKernel Pallib)
add_dependencies(PallaxKernel crti_obj crtn_obj)

# Add a dependency from the linker script to the executable
set_target_properties(PallaxKernel PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})

add_custom_command(TARGET PallaxKernel
        PRE_LINK
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_OBJECTS:crti_obj> ${CMAKE_BINARY_DIR}/crtx/crti.o
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_OBJECTS:crtn_obj> ${CMAKE_BINARY_DIR}/crtx/crtn.o
        COMMAND_EXPAND_LISTS)