
#include "chacha.h"
#include <cryptopp/chacha.h>
#include <cryptopp/osrng.h>
#include <iostream>

using namespace CryptoPP;

namespace chacha {
    void case1() {

        // 密钥和 IV
        SecByteBlock key(XChaCha20::DEFAULT_KEYLENGTH);
        // SecByteBlock iv(XChaCha20::DEFAULT_IVLENGTH);
        SecByteBlock iv(24); // XChaCha20 使用 24 字节的 IV

        // 生成随机密钥和 IV
        AutoSeededRandomPool prng;
        prng.GenerateBlock(key, key.size());
        prng.GenerateBlock(iv, iv.size());

        // 明文
        std::string plaintext = "Hello, Crypto++ with XChaCha20!";

        // 加密
        std::string ciphertext;
        XChaCha20::Encryption xchachaEncrypt;
        xchachaEncrypt.SetKeyWithIV(key, key.size(), iv);

        StringSource(plaintext, true, new StreamTransformationFilter(xchachaEncrypt, new StringSink(ciphertext)));

        std::cout << "Ciphertext: ";
        for (byte b: ciphertext) {
            std::cout << std::hex << (int) b;
        }
        std::cout << std::endl;

        // 解密
        std::string decryptedtext;
        XChaCha20::Decryption xchachaDecrypt;
        xchachaDecrypt.SetKeyWithIV(key, key.size(), iv);

        StringSource(ciphertext, true, new StreamTransformationFilter(xchachaDecrypt, new StringSink(decryptedtext)));

        // 输出解密后的明文
        std::cout << "Decrypted: " << decryptedtext << std::endl;



    } // namespace chacha
}