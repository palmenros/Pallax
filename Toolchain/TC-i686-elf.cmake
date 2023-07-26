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