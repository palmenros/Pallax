# TODO: Handle multiple architectures apart from i686

# Cross compiling options
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER i686-elf-gcc)
set(CMAKE_CXX_COMPILER i686-elf-g++)
set(CMAKE_ASM_COMPILER i686-elf-as)
set(CMAKE_AR i686-elf-ar)
set(CMAKE_OBJCOPY i686-elf-objcopy)
set(CMAKE_OBJDUMP i686-elf-objdump)
set(SIZE i686-elf-size)

# C and C++ compiler flags

# TODO: Maybe move compiler flags outside the Toolchain file?
# TODO: Change the -O2 flag depending on debug level
set(PALLAX_C_FLAGS "-O2 -ffreestanding -Wall -Wextra -fno-use-cxa-atexit")
set(PALLAX_CXX_FLAGS "${PALLAX_C_FLAGS} -fno-exceptions -fno-rtti")

set(CMAKE_C_FLAGS "${PALLAX_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${PALLAX_CXX_FLAGS}")

# Find crtbegin.o and crtend.o

execute_process(
        COMMAND ${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS} -print-file-name=crtbegin.o
        OUTPUT_VARIABLE CRTBEGIN_OBJ
)

# Remove the newline from the path
string(STRIP ${CRTBEGIN_OBJ} CRTBEGIN_OBJ)

execute_process(
        COMMAND ${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS} -print-file-name=crtend.o
        OUTPUT_VARIABLE CRTEND_OBJ
)

# Remove the newline from the path
string(STRIP ${CRTEND_OBJ} CRTEND_OBJ)

# Custom link executable which allows us to specify the order of some objects
# (which is needed for global constructors and destructors)

# TODO: Try to move this outside of the Toolchain file

# TODO: Huge hack, do not assume that crti.o and crtn.o will be in build directory
#   (we currently copy them on pre-link)
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/crtx")

set(CRTI_OBJ "${CMAKE_BINARY_DIR}/crtx/crti.o")
set(CRTN_OBJ "${CMAKE_BINARY_DIR}/crtx/crtn.o")

set(FIRST_LINKED_OBJECTS "${CRTI_OBJ} ${CRTBEGIN_OBJ}")
set(LAST_LINKED_OBJECTS "${CRTEND_OBJ} ${CRTN_OBJ}")

set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_CXX_COMPILER> <FLAGS> <LINK_FLAGS> ${FIRST_LINKED_OBJECTS} <OBJECTS> ${LAST_LINKED_OBJECTS} <LINK_LIBRARIES> -o <TARGET>")