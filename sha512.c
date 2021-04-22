#include <stdio.h>
#include <inttypes.h>

// Endianess. Adapted from:
//   https://developer.ibm.com/technologies/systems/articles/au-endianc/
#include <byteswap.h>
const int _i = 1;
#define islilend() ((*(char*)&_i) != 0)


// Words and bytes.
#define WORD uint64_t
#define PF PRIx64
#define BYTE uint8_t

// Page 5 of the secure hash standard.
#define ROTL(_x,_n) ((_x << _n) | (_x >> ((sizeof(_x)*8) - _n)))
#define ROTR(_x,_n) ((_x >> _n) | (_x << ((sizeof(_x)*8) - _n)))
#define SHR(_x,_n) (_x >> _n)

// Page 10 of the secure hash standard.
#define CH(_x,_y,_z) ((_x & _y) ^ (~_x & _z))
#define MAJ(_x,_y,_z) ((_x & _y) ^ (_x & _z) ^ (_y & _z))

#define SIG0(_x) (ROTR(_x,28)  ^ ROTR(_x,36) ^ ROTR(_x,39))
#define SIG1(_x) (ROTR(_x,14)  ^ ROTR(_x,18) ^ ROTR(_x,41))
#define Sig0(_x) (ROTR(_x,1)  ^ ROTR(_x,8) ^ SHR(_x,7))
#define Sig1(_x) (ROTR(_x,19) ^ ROTR(_x,61) ^ SHR(_x,6))

// SHA512 works on blocks of 512 bits.
union Block {
    // 8 x 64 = 512 - dealing with block as bytes.
    BYTE bytes[128];
    // 32 x 16 = 512 - dealing with block as words.
    WORD words[16];
    // 64 x 8 = 512 - dealing with the last 64 bits of last block.
    uint64_t sixf[16];
};