# aarch64-toolchain.cmake
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

set(CMAKE_C_COMPILER aarch64-unknown-linux-gnu-gcc)
set(CMAKE_STRIP aarch64-unknown-linux-gnu-strip)

# Kill macOS defaults
set(CMAKE_OSX_ARCHITECTURES "" CACHE STRING "" FORCE)
set(CMAKE_OSX_SYSROOT "" CACHE STRING "" FORCE)