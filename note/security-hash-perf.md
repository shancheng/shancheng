# Performance

Algirithm | Speed
--------- | -----
MD5 | 550 MiB/s
SHA1 | MD5 * 60%
SHA2 | MD5 * 45%
SHA3 |
AES | 3 GiB/s

Bluefish > AES > 3DES

# CPU instructions

https://en.wikipedia.org/wiki/Advanced_Vector_Extensions
GCC starting with version 4.6 (although there was a 4.3 branch with certain support) and the Intel Compiler Suite starting with version 11.1 support AVX

Hash

https://software.intel.com/en-us/articles/improving-the-performance-of-the-secure-hash-algorithm-1
Optimized SHA1 is faster than MD5

http://www.intel.com/content/dam/www/public/us/en/documents/white-papers/fast-sha512-implementations-ia-processors-paper.pdf

Three versions of SHA512 code are available in [5] which we refer to as:
1. sha512_sse4
2. sha512_avx
3. sha512_avx2_rorx

http://www.intel.com/content/dam/www/public/us/en/documents/white-papers/communications-ia-multi-buffer-paper.pdf  Multi-Buffer

To achieve the maximum performance
- Buffer count: 8+
- Buffer size: 512+

http://www.intel.com/content/dam/www/public/us/en/documents/white-papers/multi-hash-paper.pdf  Multi-Hash A Family of Cryptographic Hash Algorithm Extensions

The performance of this family of hash functions is expected to be roughly the same as a multi-buffer method. In fact, it is expected to be a little better for at least the following reasons:
1. No scheduling of buffers (of possibly different lengths) in a queue
2. Ideal interleaved layout that permits a streaming access of data and maps directly to SIMD execution units without requiring transpose operations on the data

[Is SHA-3 slow?](http://keccak.noekeon.org/is_sha3_slow.html)

# SIMD

http://www.tuicool.com/articles/UvaMzyE  SIMD-friendly algorithms for substring searching

http://0x80.pl/articles/simd-friendly-karp-rabin.html  SIMD-friendly Rabin-Karp modification
