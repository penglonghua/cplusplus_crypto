cmake_minimum_required(VERSION 3.20)

project(cryptopp_hello)

set(CMAKE_CXX_STANDARD 11)


include_directories(include)

# 设置 Crypto++ 库的路径
include_directories(/usr/local/cryptopp/include)
link_directories(/usr/local/cryptopp/lib)

add_executable(cryptopp_hello main.cpp
        src/chacha.cpp
)

# 链接 Crypto++ 库
target_link_libraries(cryptopp_hello cryptopp)