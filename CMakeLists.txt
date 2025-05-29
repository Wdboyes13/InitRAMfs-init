cmake_minimum_required(VERSION 3.21)
project(initramfs-init C)

# Static linking flags
set(CMAKE_C_FLAGS "-static -fno-pie -O2")
set(CMAKE_EXE_LINKER_FLAGS "-static -no-pie")

# Include directories
include_directories(include helpers)

# Source files
set(SRCS
        init.c
        include/utillinux/switch_root.c
        helpers/fsld.c
        helpers/mods.c
        helpers/sysmnt.c
)

# Custom library paths (static .a expected)
link_directories(${CMAKE_SOURCE_DIR}/lib)

# Add executable
add_executable(init.uns ${SRCS})

# Link required libs
target_link_libraries(init.uns blkid kmod pthread)