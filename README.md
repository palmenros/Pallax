# Pallax

Pallax is a hobby Operating-System in development. It is written using C++20.

### Folder structure

The project has the following project structure:
- `Kernel` contains all files related to the kernel
  - `Architecture` contains architecture-dependent files and drivers.
- `Toolchain` contains a CMake file with the needed cross-compilers.

### Compiling the kernel

In order to compile the Kernel, `i686-elf-binutils` and `i686-elf-g++` must be installed (or built from source for the `i686-elf` target) and in the PATH environment variable.

Once the prerrequisites are met run the following commands from the repository root folder:

```shell
mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../Toolchain/TC-i686-elf.cmake ..
cmake --build .
```

### Executing the kernel 

The result of compiling the kernel is an ELF Multiboot image. It can be loaded using Qemu:
```shell
qemu-system-i386 -kernel build/Kernel/PallaxKernel
```