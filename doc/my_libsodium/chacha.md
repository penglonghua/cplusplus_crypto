# chacha

> https://doc.libsodium.org/advanced/stream_ciphers/chacha20

ChaCha20 is a stream cipher developed by Daniel J. Bernstein. 

> 作者 是同一个的 Daniel J. Bernstein.

```text
Its original design expands a 256-bit key into 2^64 randomly accessible streams, each containing 2^64 randomly accessible 64-byte (512 bits) blocks. It is a variant of Salsa20 with better diffusion.

```

输入，输出的是什么？ 

ChaCha20 doesn’t require any lookup tables and avoids the possibility of timing attacks.

Internally(内部的), ChaCha20 works like a block cipher used in counter mode.
It includes an internal block counter to avoid incrementing the nonce after each block.

Two variants of the ChaCha20 cipher are implemented in libsodium:

* The original ChaCha20 cipher with a 64-bit nonce and a 64-bit counter, allowing a practically unlimited amount of data to be encrypted with the same (key, nonce) pair.

* The `IETF` variant increases the nonce size to 96 bits, but reduces the counter size down to 32 bits, allowing only up to 256 GB of data to be safely encrypted with a given (key, nonce) pair.

> 这个地方就是要分 32位 和 64位的. 注意一下. 看一下的 counter.

These primitives should only be used to implement protocols that specifically require them. 
For all other applications, it is recommended to use the high-level crypto_stream API (`XSalsa20`) or the ChaCha20-based construction with an extended nonce, `XChaCha20` (crypto_stream_xchacha20).


> rust 中会是怎么样的？

> 关键字 `IETF`



## Usage (original construction)



这个函数怎么说明的 以及使用.



```c

int crypto_stream_chacha20(
    unsigned char *c,            // 输出缓冲区，用于存储伪随机流 (char* 字符数组)
    unsigned long long clen,     // 要生成的伪随机流的字节数 (long ) , 就是上面的 char 字节大小
    const unsigned char *n,      // Nonce（随机数/唯一值），长度为 crypto_stream_chacha20_NONCEBYTES  (char * )
    const unsigned char *k       // Key（密钥），长度为 crypto_stream_chacha20_KEYBYTES (char *)


);

```

参数说明
c:

类型：unsigned char *
描述：输出缓冲区，用于存储生成的伪随机流。调用者需要确保 c 有足够的内存分配（至少为 clen 字节）。
使用场景：
可以直接使用生成的流作为加密数据。
可以结合明文（通过 XOR 操作）实现加密/解密。

clen:

类型：unsigned long long
描述：生成伪随机流的长度（以字节为单位）。
注意：
长度不能超过算法的限制（2^64 - 1 字节）。
确保分配的 c 足够大以容纳此长度。

n (Nonce):

类型：const unsigned char *
描述：Nonce（随机数或唯一值）是输入的一部分，必须是长度为 crypto_stream_chacha20_NONCEBYTES 字节（通常为 8 或 12 字节）。
注意：
Nonce 必须在每次加密过程中唯一。
重复使用相同的密钥和 Nonce 会导致安全问题。

k (Key):

类型：const unsigned char *
描述：对称密钥，长度必须为 crypto_stream_chacha20_KEYBYTES（32 字节）。
注意：
密钥必须是随机的、高熵的，并妥善保密。

返回值
成功：返回 0。
错误：通常不会发生，libsodium 的设计确保正确使用时不会有运行时错误。

相关常量
crypto_stream_chacha20_KEYBYTES:

描述：密钥长度，固定为 32 字节。
定义：#define crypto_stream_chacha20_KEYBYTES 32

crypto_stream_chacha20_NONCEBYTES:

描述：Nonce 长度，固定为 8 或 12 字节，具体取决于实现。
定义：#define crypto_stream_chacha20_NONCEBYTES 12

如何使用这个函数.


```c

int crypto_stream_chacha20_xor(unsigned char *c, const unsigned char *m,
                               unsigned long long mlen, const unsigned char *n,
                               const unsigned char *k);

```

The `crypto_stream_chacha20_xor()` function encrypts a message `m` of length `mlen` using a nonce n (crypto_stream_chacha20_NONCEBYTES bytes) and a secret key k (crypto_stream_chacha20_KEYBYTES bytes).

The ciphertext is put into `c`. The ciphertext is the message combined with the output of the stream cipher using the XOR operation, and doesn’t include any authentication tag.

`m` and `c`can point to the same address (in-place encryption/decryption). If they don’t, the regions should not overlap.

> 这个地方就是 加密和解密的.

继续该例子.


The `crypto_stream_chacha20_xor_ic()` function is similar to `crypto_stream_chacha20_xor()` but adds the ability to set the initial value of the block counter to a non-zero value, `ic`
This permits direct access to any block without having to compute the previous ones.


> but with the addition of an initial counter (ic), which provides more flexibility for nonces in certain scenarios.

The primary difference between crypto_stream_chacha20_xor and crypto_stream_chacha20_xor_ic is that crypto_stream_chacha20_xor_ic allows you to specify a counter (ic) in addition to the nonce, 
enabling you to use it in a wider range of applications, especially when you want to control the counter increment or reuse the same nonce in different contexts while maintaining security.

```c

int crypto_stream_chacha20_xor_ic(unsigned char *c,
                                   const unsigned char *m,
                                   unsigned long long mlen,
                                   const unsigned char *n,
                                   unsigned long long ic,  // initial counter
                                   const unsigned char *k);


```

这个例子如何使用?
ic: The 64-bit integer used as the initial counter (used with the nonce).

计数器 (ic)：在 crypto_stream_chacha20_xor_ic 中，您可以控制计数器的初始值，并根据需要增加它。它与 nonce 一起确定伪随机流的生成。
例如，ic 可以在多个消息的加密中保持不变，或者您可以逐步增加 ic 以避免重复使用相同的 nonce 和 ic 组合。
输出：密文输出被以十六进制打印出来，可以帮助调试和验证加密过程的正确性。解密时，密文应该被还原为原始明文。


## Usage (IETF variant, message length limited to 256 GB)

同样的 3个函数

```c

int crypto_stream_chacha20_ietf(unsigned char *c, unsigned long long clen,
                               const unsigned char *n, const unsigned char *k);

int crypto_stream_chacha20_ietf_xor(unsigned char *c, const unsigned char *m,
                                    unsigned long long mlen, const unsigned char *n,
                                    const unsigned char *k);  

int crypto_stream_chacha20_ietf_xor_ic(unsigned char *c, const unsigned char *m,
                                       unsigned long long mlen,
                                       const unsigned char *n, uint32_t ic,
                                       const unsigned char *k);                                                                 
```