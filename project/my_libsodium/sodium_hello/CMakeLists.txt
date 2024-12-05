cmake_minimum_required(VERSION 3.20)
project(sodium_hello C)


set(CMAKE_C_STANDARD 11)


# 引入 pkg-config 模块
find_package(PkgConfig REQUIRED)


# 检查 libsodium 的 pkg-config 信息
pkg_check_modules(LIBSODIUM REQUIRED libsodium)

# 添加 include 路径和库路径
include_directories(${LIBSODIUM_INCLUDE_DIRS} include)


link_directories(${LIBSODIUM_LIBRARY_DIRS})

add_executable(sodium_hello main.c
        src/rand.c
        src/util.c
)


# 链接 libsodium 库
target_link_libraries(sodium_hello ${LIBSODIUM_LIBRARIES})