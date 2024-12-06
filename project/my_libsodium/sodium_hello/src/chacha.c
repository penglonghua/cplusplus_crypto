#include "chacha.h"
#include <sodium.h>
#include <stdlib.h>
#include <string.h>


int chacha_case1() {


    if (sodium_init() < 0) {
        // 初始化失败
        fprintf(stderr, "Failed to initialize libsodium!\n");
        return 1;
    }

    // 定义伪随机流的长度
    size_t stream_length = 64; // 生成 64 字节的伪随机流

    // 缓冲区
    unsigned char stream[stream_length];

    // 密钥和 nonce
    // unsigned char key[crypto_stream_chacha20_KEYBYTES]; // 32 字节
    // unsigned char nonce[crypto_stream_chacha20_NONCEBYTES]; // 8 字节
    //
    // // 随机生成密钥和 nonce
    // randombytes_buf(key, sizeof(key));
    // randombytes_buf(nonce, sizeof(nonce));

    // 只要 key 和 nonce 一样，每次随机都是一样的
    const char *key_string = "thisisaverylongkeyforchacha20"; // 32字节
    const char *nonce_string = "nonce123"; // 8 字节

    unsigned char key[crypto_stream_chacha20_KEYBYTES];
    unsigned char nonce[crypto_stream_chacha20_NONCEBYTES];
    memcpy(key, key_string, crypto_stream_chacha20_KEYBYTES); //
    memcpy(nonce, nonce_string, crypto_stream_chacha20_NONCEBYTES); //


    // 使用 crypto_stream_chacha20 生成伪随机流
    if (crypto_stream_chacha20(stream, stream_length, nonce, key) != 0) {
        fprintf(stderr, "Failed to generate stream\n");
        return 1;
    }

    // 打印生成的伪随机流（以十六进制形式显示）
    printf("Generated ChaCha20 random stream:\n");
    for (size_t i = 0; i < stream_length; i++) {
        printf("%02x", stream[i]); // x 是 16进制
    }
    printf("\n");

    return 0;
}


int chacha_case2() {


    if (sodium_init() < 0) {
        printf("libsodium 初始化失败\n");
        return -1;
    }

    // 初始化密钥和随机数
    // unsigned char key[crypto_stream_chacha20_KEYBYTES];
    // unsigned char nonce[crypto_stream_chacha20_NONCEBYTES];
    // randombytes_buf(key, sizeof key);
    // randombytes_buf(nonce, sizeof nonce);


    // 固定的密钥和随机数字符串
    const char *key_string = "thisisaverylongkeyforchacha20";
    const char *nonce_string = "nonce123";

    // 将字符串转换为字节数组
    unsigned char key[crypto_stream_chacha20_KEYBYTES];
    unsigned char nonce[crypto_stream_chacha20_NONCEBYTES];
    memcpy(key, key_string, crypto_stream_chacha20_KEYBYTES);
    memcpy(nonce, nonce_string, crypto_stream_chacha20_NONCEBYTES);

    // 输入明文
    const char *plaintext = "Hello, this is a secret message!";
    unsigned long long plaintext_len = strlen(plaintext);
    unsigned char ciphertext[plaintext_len]; // 用于存储密文
    unsigned char decrypted[plaintext_len]; // 用于存储解密后的数据

    // 加密
    crypto_stream_chacha20_xor(ciphertext, (const unsigned char *) plaintext, plaintext_len, nonce, key);
    printf("加密成功!\n");
    printf("加密后的密文:\n");
    for (size_t i = 0; i < plaintext_len; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");

    // 解密
    crypto_stream_chacha20_xor(decrypted, ciphertext, plaintext_len, nonce, key);
    // 确保输出解密后的明文为字符串形式  解决乱码问题的
    decrypted[plaintext_len] = '\0'; // 添加字符串结束符 , 修复 乱码
    printf("解密后的明文: %s\n", decrypted); // FIXME: 有乱码.

    return 0;
}

int chacha_case3() {
    if (sodium_init() < 0) {
        printf("libsodium 初始化失败\n");
        return -1;
    }

    // 固定的密钥和随机数字符串
    const char *key_string = "thisisaverylongkeyforchacha20";
    const char *nonce_string = "nonce123";

    // 将字符串转换为字节数组
    unsigned char key[crypto_stream_chacha20_KEYBYTES];
    unsigned char nonce[crypto_stream_chacha20_NONCEBYTES];
    memcpy(key, key_string, crypto_stream_chacha20_KEYBYTES);
    memcpy(nonce, nonce_string, crypto_stream_chacha20_NONCEBYTES);

    // 输入明文
    const char *plaintext = "Hello, this is a secret message!";
    unsigned long long plaintext_len = strlen(plaintext);
    unsigned char ciphertext[plaintext_len]; // 用于存储密文
    unsigned char decrypted[plaintext_len]; // 用于存储解密后的数据

    unsigned long long ic = 1; // 初始计数器 (可以根据需要调整)

    // 加密
    crypto_stream_chacha20_xor_ic(ciphertext, (const unsigned char *)plaintext, plaintext_len, nonce, ic, key);
    printf("加密后的密文:\n");
    for (size_t i = 0; i < plaintext_len; i++) {
        printf("%02x ", ciphertext[i]);  // 将每个字节以两位十六进制打印
    }
    printf("\n");

    // 解密
    crypto_stream_chacha20_xor_ic(decrypted, ciphertext, plaintext_len, nonce, ic, key);

    // 确保输出解密后的明文为字符串形式
    decrypted[plaintext_len] = '\0';  // 添加字符串结束符
    printf("解密后的明文: %s\n", decrypted);

    return 0;
}