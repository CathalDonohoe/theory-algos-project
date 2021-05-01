# Theory-Algos-Project
## Description of this repository
This repository houses the Theory of Algorithms module from Galway-Mayo Institute of Technology's Software Development course.
 <br>
The project's aim is to write a C program that calculates the SHA512 value of an input file.<br>
The software must take the file's name or route as a command line argument and return its SHA512 digest. Other than what is included in the C standard library, this program does not use any external libraries.<br>
The software must compile with `gcc` or `clang`, and it must provide a MakeFile that compiles it when the project folder's `make` command is called.<br>
The Makefile must contain tests that run when the make test command is executed. 

## What is Secure Hash Standard
The Secure Hash Algorithm was developed by NIST, specified in the Secure Hash Standard, originally in 1993. They were revised as SHA-1 in 1995 that produced a 160 bit hash. NIST specified SHA-2 algorithms in 2002. The Secure Hash algorithms are a family of cryptographic hash functions published by the National Institute of Standards of Technology as a U.S. Federal Information Processing Standard[2]. These algorithms are used to create message digests. <br>
All of the algorithms are iterative one-way hash functions that can process a message and generate a message digest. <br>
It transforms data using a hash function, which is an algorithm made up of bitwise operations, modular additions, and compression functions. The hash function then generates a fixed-length string that bears no resemblance to the original. <br>
Many items use hashing algorithms, like internet protection, digital certificates, and even blockchains.<br>
<img src="https://gcn.com/-/media/GIG/GCN/Redesign/Articles/2015/August/sha3.png">


## What is SHA-512
SHA-512 is a function of cryptographic algorithm SHA-2, which is an evolution of SHA-1. The SHA-2 family consists of six hash functions with digests that are 224, 256, 384 or 512 bits: SHA-224, SHA-256, SHA-384, SHA-512, SHA-512/224, SHA-512/256. SHA-512 is a novel hash function computed with eight 64-bit words. SHA-512 is very close to SHA-256 except that it uses 1024 bits "blocks", and accepts a 2^128 bits maximum length string at its input.
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
The SHA512 function cannot be decrypted or revered since it is a one-way function rather than an encryption function.
Many people mistakenly believe that SHA-512 encrypts data.
It doesn't work like that.
It simply calculates a hash value for a collection of data.
One-way methods such as hash functions are used.
They calculate hash values(digets) from the data (messages).
It's impossible to do the same.  To better explain why a SHA-512 is NOT reversible, here's very simple example: <br>
Using SHA-512 on text data of 750,000 characters, we obtain a mere 128 digits digest. Now if I wanted to revert this, how could I possibly determine with exactitude which 750,000 characters were used from just 128 digits? <br>
 The fundamental difference is that while encryption is a two way function(given the key) hash is only a one way function: given some data you can compute the hash, given the hash it is difficult to have the data back. In these cases, it is computationally unfeasible to find the reverse of a hash, but it is easy to find the hash of any data. Reversing a hash function would cause a preimage attack. <br>
	“In cryptography, a preimage attack on cryptographic hash functions tries to find a message that has a specific hash value. A cryptographic hash function would resist attacks on its preimage (set of possible inputs).” [1] <br>
	Some of the features that a hashing algorithm use that can be contributed as to what makes theme non-reversable: <br>
•	Bit-dependency: A hash algorithm is designed to ensure that each bit of the output is dependant upon every bit in the input. This prevents anyone from splitting the algorithm up and trying to reverse calculate an input from each bit of the output has separately. To solve an output bit, you must know the full input, requiring the attempt to know all or nothing. <br>
•	Avalanching: Related to bit dependency, a change in a single bit in the input is designed to result in a huge change in the internal state of the algorithm and the output. Since the output changes so dramatically with each input bit change, this stops people from building relationships between inputs and outputs. Give example here <br>
•	Non-linearity: Hashing algorithms always contain non-linear operations – this prevents people from using linear algebra techniques to solve the input from a given output.  Building a hash algorithm using just addition operators is a terrible idea, that’s why most hashing algorithms use many combinations of linear and non-linear operations. <br>

## Can you design an algorithm that, given enough time, will find input messages that give each of the possible 512-bit strings?
The problem with this question begins in how many possible 512-bit strings exist from the output of the SHA-512 algorithm. We don’t know how large the range of the SHA-512 function is. It is assumed to be very close to 2^512, which would be all possible 512-bit values. This leads us to a more important question; how long would it take to compute all the possible 512-bit strings? Well if we were to start by computing our 2^512 into human numbers, we would get: <br>
2^512 = 13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084096 <br>
This number is close to 0.1% of the atoms in the visible universe, so it goes without saying that there are a lot of possible values from the SHA-512 algorithm. To put this equation into perspective, ill use Bitcoin as an example. Bitcoin uses SHA-256, which I am aware has a completely different number of possible strings values but is comparable to SHA-512 none the less. <br>
Since January 2015, Bitcoin has been computing 300 quadrillion SHA-256 hashes per second. That’s 300 x 1015 hashes per second. If we were trying to give each of the possible values, we would first need to compute every value, and then compute it yet again to ensure all possible values have been computed. To do this with SHA-512, we would only need to calculate 2^256 hashes. If we were to take Bitcoins current progress with SHA-256: <br>
2^128 / (300 x 10^15 .86400.365.25) = 3.6 x 10^13 years. For comparison, our universe is only about 13.7 x 10^9 years old. Yet again, this is with SHA-256, which means that computing all the possible 512-bit strings would be an even larger number exponentially.  <br>
So, to answer the question “Can you design an algorithm that, given enough time, will find input messages that give each of the possible 512-bit strings?”, then my answer would be “Yes”. It is possible but given enough time. The time is the problem, we would need more years than our own universe is today. This is under the assumption that we know the full range of the SHA-512 algorithm, which we currently don’t. The algorithm would take longer than the universe is currently, but it is possible, just not feasible. <br>


## How difficult is it to find a hash digest beginning with at least twelve zeros?
With SHA-512, a message digest algorithm or a hash funciton, is a procedure that maps input data of an arbitary length to an output of fixed length. Output is often known as hash values or hash digests [8]. These digests are a series of numbers and characters. The length of these digests, in the case of SHA-512, are 128 characters. This means that there are only a certain amount of posible digest outputs, more than the variable of inputs. Therefore we may result with the same output for 2 different inputs. <br>
With this question, I am going to refer to what Botcoin miners are currently doing to mine bitcoin. In crypotocurrency mining, a target hash is a numeric value that a hashed block header must be less than or equal to in order for a new block to be awarded to a miner [9]. Miners make these guesses by randomly generating as many "nonces" as possible, as fast as possible [10]. 
A nonce is short for "number only used once". Nonces are often used on authentication protocols and cryptographic hash functions [11]. The first miner whose nonce generates a hash that is less than or equal to the target hash is awarded credit for completing that block and is awarded the spoils of 6.25 BTC [10]. 
All target hashes begin with zeroes - at least eight zeroes and up to 63 zeroes.  There is no minimum target, but there is a maximum target set by the Bitcoin Protocol. No target can be greater than this number: <br>

* 00000000ffff0000000000000000000000000000000000000000000000000000 <br>

This method is the simplest method I can think of when it comes to computing the hash digest in question. But interesting enough, this has been done as of 2017. For years there was a competition to find an ASCII string whose SHA-512 hash value is as low as possible(Which roughly speaking means having as many leading zeroes). This was solved by a programmer by the name of Nayuki. He did this by nuilding a brute-force search program. Surprisingly enough, the lowest SHA-512 value he could calculate was:
* 000000000000363356970fe81fd24bb30019cefcdf34f1ba29ea99871297f621a0f3351ae41f1109b49261a3246c83e59e182f7a12431291da1db2cda80ddf17  [13]<br>

This value has exactly twelve zeroes at the start of the hash value. so to summerise my answer to "How difficult is it to find a hash digest beginning with at least twelve zeros?", it is so difficult to do that you may just win a competition and beat a record if you can manage to do so.


[1] https://en.wikipedia.org/wiki/Preimage_attack <br>
[2] https://en.wikipedia.org/wiki/Secure_Hash_Algorithms <br>
[3] https://www.youtube.com/watch?v=KQgMTNuj-S8 <br>
[4] https://www.youtube.com/watch?v=5OVb4I5fhKI <br>
[5] https://www.youtube.com/watch?v=wNBlwmJQbC8 <br>
[6] https://en.bitcoinwiki.org/wiki/SHA-512 <br>
[7] https://medium.com/@zaid960928/cryptography-explaining-sha-512-ad896365a0c1 <br>
[8] https://www.veracode.com/blog/research/message-digests-aka-hashing-functions <br>
[9] https://www.investopedia.com/terms/t/target-hash.asp <br>
[10] https://www.investopedia.com/tech/how-does-bitcoin-mining-work/ <br>
[11] https://academy.binance.com/en/glossary/nonce <br>
[12] https://www.nayuki.io/page/lowest-sha512-value-by-brute-force <br>
[13]https://web.archive.org/web/20171002020748/http://www.h11e.com/ <br>
[14]https://dev.to/damcosset/trying-to-understand-blockchain-by-making-one-ce4 <br>
[15]https://en.wikipedia.org/wiki/Cryptographic_hash_function <br>
[16]https://yukimotopress.github.io/programming-blockchains-step-by-step <br>
[17]https://bitcoin.stackexchange.com/questions/65478/which-is-the-smallest-hash-that-has-ever-been-hashed  
[18]https://bitcointalk.org/index.php?topic=29675.0  
[19]https://www.reddit.com/r/programming/comments/1y17al/hashchallenge_can_you_find_the_lowest_value/  
[20]https://www.simplilearn.com/bitcoin-mining-explained-article  
[21]https://www.freecodecamp.org/news/how-bitcoin-mining-really-works-38563ec38c87/  
[22]http://www.righto.com/2014/09/mining-bitcoin-with-pencil-and-paper.html  
[23]https://crypto.stackexchange.com/questions/89690/sha-512-how-difficult-is-it-to-find-a-hash-digest-beginning-with-at-least-twel  
[24]https://www.investopedia.com/terms/n/nonce.asp  
[25]https://en.bitcoin.it/wiki/Nonce  
[26]https://www.sciencedirect.com/topics/computer-science/hash-digest  
[27]https://www.thesslstore.com/blog/what-is-a-hash-function-in-cryptography-a-beginners-guide/  
[28]https://cleartax.in/g/terms/target-hash  
[29]http://www.iwar.org.uk/comsec/resources/cipher/sha256-384-512.pdf 
[30]https://core.ac.uk/download/pdf/186473296.pdf  