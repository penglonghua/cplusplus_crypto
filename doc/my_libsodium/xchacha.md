# XChaCha20


XChaCha20 is a variant of ChaCha20 with an extended nonce, allowing random nonces to be safe.

XChaCha20 doesn’t require any lookup tables and avoids the possibility of timing attacks.

Internally, XChaCha20 works like a block cipher used in counter mode. It uses the HChaCha20 hash function to derive a subkey and a subnonce from the original key and extended nonce, and a dedicated 64-bit block counter to avoid incrementing the nonce after each block.



> XChaCha20 is generally recommended over plain ChaCha20 due to its extended nonce size, and its comparable performance. However, XChaCha20 is currently not widely implemented outside the libsodium library, due to the absence of formal specification.

> 推荐使用的.

## 

```c

int crypto_stream_xchacha20(unsigned char *c, unsigned long long clen,
                            const unsigned char *n, const unsigned char *k);


int crypto_stream_xchacha20_xor(unsigned char *c, const unsigned char *m,
                                unsigned long long mlen, const unsigned char *n,
                                const unsigned char *k);


int crypto_stream_xchacha20_xor_ic(unsigned char *c, const unsigned char *m,
                                   unsigned long long mlen,
                                   const unsigned char *n, uint64_t ic,
                                   const unsigned char *k);

```


这个地方多了一个辅助函数

```c
void crypto_stream_xchacha20_keygen(unsigned char k[crypto_stream_xchacha20_KEYBYTES]);

```
This helper function introduced in libsodium 1.0.12 creates a random key k.

It is equivalent to calling `randombytes_buf()` but improves code clarity and can prevent misuse by ensuring that the provided key length is always be correct.


