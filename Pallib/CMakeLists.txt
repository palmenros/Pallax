add_library(Pallib STATIC OutputStream.h OutputStream.cpp)
target_include_directories(Pallib INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/..")
