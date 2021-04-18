# theory-algos-project
## Why can't we reverse the SHA512 algorithm to retrieve the original message from a hash digest?
The SHA512 function cannot be decrypted or revered as it is not an encryption function as it’s a one-way function. A lot of people are under the impression that SHA-512 encrypts data. It does no such thing. All it does is compute a hash value for a given set of data. Hash functions are used as one-way methods. They take the data (messages) and compute hash values (digests). The inverse can't be done. To better explain why a SHA-512 is NOT reversible, here's very simple example:
Using SHA-512 on text data of 750,000 characters, we obtain a mere 128 digits digest. Now if I wanted to revert this, how could I possibly determine with exactitude which 750,000 characters were used from just 128 digits? <br>
 The fundamental difference is that while encryption is a two way function(given the key) hash is only a one way function: given some data you can compute the hash, given the hash it is difficult to have the data back. In these cases, it is computationally unfeasible to find the reverse of a hash, but it is easy to find the hash of any data. Reversing a hash function would cause a preimage attack. <br>
	“In cryptography, a preimage attack on cryptographic hash functions tries to find a message that has a specific hash value. A cryptographic hash function would resist attacks on its preimage (set of possible inputs).” [1] <br>
	Some of the features that a hashing algorithm use that can be contributed as to what makes theme non-reversable: <br>
•	Bit-dependency: A hash algorithm is designed to ensure that each bit of the output is dependant upon every bit in the input. This prevents anyone from splitting the algorithm up and trying to reverse calculate an input from each bit of the output has separately. To solve an output bit, you must know the full input, requiring the attempt to know all or nothing. <br>
•	Avalanching: Related to bit dependency, a change in a single bit in the input is designed to result in a huge change in the internal state of the algorithm and the output. Since the output changes so dramatically with each input bit change, this stops people from building relationships between inputs and outputs. Give example here <br>
•	Non-linearity: Hashing algorithms always contain non-linear operations – this prevents people from using linear algebra techniques to solve the input from a given output.  Building a hash algorithm using just addition operators is a terrible idea, that’s why most hashing algorithms use many combinations of linear and non-linear operations. <br>






[1] https://en.wikipedia.org/wiki/Preimage_attack
