add_library(PalLib STATIC OutputStream.h OutputStream.cpp Optional.h StdLibExtras.h TypeTraits.h StringView.cpp StringView.h)
target_include_directories(PalLib INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/..")
