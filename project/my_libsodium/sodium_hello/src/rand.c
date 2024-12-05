#include "rand.h"
#include <sodium.h>
#include <stdio.h>


int rand_case1(void) {

    if (sodium_init() < 0) {
        // 初始化失败
        fprintf(stderr, "Failed to initialize libsodium!\n");
        return 1;
    }

    // 生成随机字节
    unsigned char random_bytes[16]; // 定义一个 16 字节的数组
    randombytes_buf(random_bytes, sizeof(random_bytes));

    // 打印随机字节
    printf("Generated random bytes: ");
    for (size_t i = 0; i < sizeof(random_bytes); i++) {
        printf("%02x ", random_bytes[i]);
    }
    printf("\n");
}
