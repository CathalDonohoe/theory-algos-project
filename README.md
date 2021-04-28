# Theory-Algos-Project
## Description of this repository
This repository is for the module Theory of Algorithms for the Software Development course in Galway-Mayo Institute of Technology <br>
The goal of the project is to write a program in the C programming language to calculate the SHA512 value of an input file. The program must take the name or the path of the file as a command line argument and output the SHA512 digest of it. This program does not use any external libaries other than what is included in the C standard library. The program must compile using `gcc` or `clang` and must include a MakeFile which compiles it upon `make` being called in the project folder. The Makefile must include tests which run upon `make test` being called.

## What is Secure Hash Standard
The Secure Hash Algorithm was developed by NIST, specified in the Secure Hash Standard, originally in 1993. They were revised as SHA-1 in 1995 that produced a 160 bit hash. NIST specified SHA-2 algorithms in 2002. The Secure Hash algorithms are a family of cryptographic hash functions published by the National Institute of Standards of Technology as a U.S. Federal Information Processing Standard[2]. These algorithms are used to generate digests of messages. All of the algorithms are iterative, one-way hash functions that can process a message to produce a condensed representation called a message digest. It works by transforming the data using a hash function: an algorithm that consists of bitwise operations, modular additions, and compressions funcitons. The hash function then produces a fixed-size string that looks nothing like the original. Hashing algorithms are used in many things such as internet security, digital certificates and even blockchains.<br>
<img src="https://gcn.com/-/media/GIG/GCN/Redesign/Articles/2015/August/sha3.png">


## What is SHA-512
SHA-512 is a funciton of cryptographic algorithm SHA-2, which is an evolution of SHA-1. The SHA-2 family consists of six hash functions with digests that are 224, 256, 384 or 512 bits: SHA-224, SHA-256, SHA-384, SHA-512, SHA-512/224, SHA-512/256. SHA-512 is a novel hash function computed with eight 64-bit words. SHA-512 is very close to SHA-256 except that it uses 1024 bits "blocks", and accepts a 2^128 bits maximum length string at its input.
<img src="https://www.researchgate.net/profile/Nivethitha-Somu/publication/282937655/figure/tbl3/AS:667063395819524@1536051715760/Comparisons-on-SHA-based-on-Key-size.png"> <br>
<br>
SHA-512 is identical in structure to SHA-256 but:
* The message is broken into 1024-bit chunks
* The initial hash values and round constants are extended to 64 bits
* There are 80 rounds instead of 64
* The message schedule array has 80 – 64-bit words instead of 64 – 32-bit words
* To extend the message schedule array w, the loop is from 16 to 79 instead of from 16 to 63
* The round constants are based on the first 80 primes 2..409
* The word size used for calculations is 64 bits long
* The appended length of the message (before pre-processing), in bits, is a 128-bit big-endian integer
* And the shift and rotate amounts used are different.
<br>

## How the code works
### Symbols and Operations
* The Boolean Operations AND, XOR and OR, denoted by ∧, ⊕ and ∨, respectively. <br>
* ROTR (n(x)=(x>> n) (x<< w -n)) - The rotate right operation, where x is a w-bit word and n is an integer with 0 <= n < w <br>
* SHR (n(x)=x>> n) - The right shift operation, where x is a w-bit word and n is an integer with 0 <= n < w <br>
The following code is how i have implemented these operations into my SHA-512 program <br>
<img src="https://gyazo.com/d787676346a0ece94a8fe51c0cf8f5ee.png"> <br>

### Functions and Constants
SHA-512 uses six logical functions, where each function operates on 64-bit words, which are represented as x,y, and z. <br>
<img src="https://gyazo.com/439910e1257b49f58029fb2960201a3e.png"> <br>
These are implemented in my code through the following: <br>
```#define CH(_x,_y,_z) ((_x & _y) ^ (~_x & _z))
#define MAJ(_x,_y,_z) ((_x & _y) ^ (_x & _z) ^ (_y & _z))

#define SIG0(_x) (ROTR(_x,28)  ^ ROTR(_x,34) ^ ROTR(_x,39))
#define SIG1(_x) (ROTR(_x,14)  ^ ROTR(_x,18) ^ ROTR(_x,41))
#define Sig0(_x) (ROTR(_x,1)  ^ ROTR(_x,8) ^ SHR(_x,7))
#define Sig1(_x) (ROTR(_x,19) ^ ROTR(_x,61) ^ SHR(_x,6))
```
SHA-512 uses the same sequence of eighty constant 64-bit words. These words represent the sixty-four bits of the fractional parts cube roots of the first eighty prime numbers. these are implemented into my program through this constant: <br>
```
const WORD K[] = {

    0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
    0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
    0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
    0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
    0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
    0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
    0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
    0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
    0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
    0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
    0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
    0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
    0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
    0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
    0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
    0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
    0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
    0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
    0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
    0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817
}; 
```
### PreProcessing
Preprocessing consists of three steps:
* Padding the message
* Parsing the message into the message blocks
* Setting the hash value

Padding the Message! <br>
the purpose of this padding is to ensure that the padded message is a multiple of 1024. For example, the (8-bit ASCII) message "abc" has length 8x3=24, so the message is padded with a one bit, then 896-(24+1)=871 zero bits, and then the message length, to become the 1024-bit padded message. The length of the padded message should now be a multiple of 1024 bits. <br>
This can be seen adapted in my code here: <br>
<img src = "https://gyazo.com/49da9f5c9eda96ceb1961ffc54bc9d11.png"> <br>

Parsing the Message! <br>
The message and its padding must be parsed into N 1024-bit blocks. Since the 1024 bits of the input block may be expressed as sixteen 64-bit words, the first 64 bits of the message block i are denoted M ∈ {i, 0}, the next 64 bits are denoted  M ∈ {i, 1}, and so on up to  M ∈ {i, 15}. <br>

Setting the hash value! <br>
Before hash computation begins for each of the secure hash algorithms, the initial hash vale H^0, must be set. The size of the words in H^0 depends on the message digest size. <br>
Each message block is processed in order using the following steps: <br>
* Prepare the schedule <br>
<img src = "https://gyazo.com/f0e29d56f46ad5d311a96a611eb8b373.png"> <br>
* Initialize  the  eight  working  variables, a, b, c, d, e, f, g,  and h,  with  the  (i-1)st hash value <br>
<img src = "https://gyazo.com/79c21f61f420ba74e1140272169a5ff1.png"> <br>
* For t=0 to 79 <br>
<img src = "https://gyazo.com/7fa4be8a3691c950c69d17a5378712f6.png"> <br>
* Compute the ith intermediate hash value H(i) <br>
<img src = "https://gyazo.com/59f53f89a8d4c0e1362fffca3b6789e5.png"> <br>
<br>

<br>
These components together make the SHA-512 algorithm programmed in the C Programming Language. TBC

## Why can't we reverse the SHA512 algorithm to retrieve the original message from a hash digest?
The SHA512 function cannot be decrypted or revered as it is not an encryption function as it’s a one-way function. A lot of people are under the impression that SHA-512 encrypts data. It does no such thing. All it does is compute a hash value for a given set of data. Hash functions are used as one-way methods. They take the data (messages) and compute hash values (digests). The inverse can't be done. To better explain why a SHA-512 is NOT reversible, here's very simple example:
Using SHA-512 on text data of 750,000 characters, we obtain a mere 128 digits digest. Now if I wanted to revert this, how could I possibly determine with exactitude which 750,000 characters were used from just 128 digits? <br>
 The fundamental difference is that while encryption is a two way function(given the key) hash is only a one way function: given some data you can compute the hash, given the hash it is difficult to have the data back. In these cases, it is computationally unfeasible to find the reverse of a hash, but it is easy to find the hash of any data. Reversing a hash function would cause a preimage attack. <br>
	“In cryptography, a preimage attack on cryptographic hash functions tries to find a message that has a specific hash value. A cryptographic hash function would resist attacks on its preimage (set of possible inputs).” [1] <br>
	Some of the features that a hashing algorithm use that can be contributed as to what makes theme non-reversable: <br>
•	Bit-dependency: A hash algorithm is designed to ensure that each bit of the output is dependant upon every bit in the input. This prevents anyone from splitting the algorithm up and trying to reverse calculate an input from each bit of the output has separately. To solve an output bit, you must know the full input, requiring the attempt to know all or nothing. <br>
•	Avalanching: Related to bit dependency, a change in a single bit in the input is designed to result in a huge change in the internal state of the algorithm and the output. Since the output changes so dramatically with each input bit change, this stops people from building relationships between inputs and outputs. Give example here <br>
•	Non-linearity: Hashing algorithms always contain non-linear operations – this prevents people from using linear algebra techniques to solve the input from a given output.  Building a hash algorithm using just addition operators is a terrible idea, that’s why most hashing algorithms use many combinations of linear and non-linear operations. <br>

## Can you design an algorithm that, given enough time, will find input messages that give each of the possible 512-bit strings?


## How difficult is it to find a hash digest beginning with at least twelve zeros?
very difficult



[1] https://en.wikipedia.org/wiki/Preimage_attack <br>
[2] https://en.wikipedia.org/wiki/Secure_Hash_Algorithms <br>
[3] https://www.youtube.com/watch?v=KQgMTNuj-S8 <br>
[4] https://www.youtube.com/watch?v=5OVb4I5fhKI <br>
[5] https://www.youtube.com/watch?v=wNBlwmJQbC8 <br>
[6] https://en.bitcoinwiki.org/wiki/SHA-512 <br>
