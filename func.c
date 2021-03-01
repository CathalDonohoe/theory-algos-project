#include <stdio.h>
#include <inttypes.h>

#define W 32
#define WORD uint32_t
#define PF PRIX32
#define CH(x,y,z) (x&y)^(~x&z)
#define MAJ(x,y,z) (x&y)^(x&z)^(y&z)


#define ROTL(x,n) (x<<n)|(x>>(W-n))
#define ROTR(x,n) (x>>n)|(x<<(W-n))
#define SHR(x,n) x>>n

#define SIG0(x) ROTR(x,2)^ROTR(x,13)^ROTR(x,22)
#define SIG1(x) ROTR(x,6)^ROTR(x,11)^ROTR(x,25)
#define Sig0(x) ROTR(x,7)^ROTR(x,18)^SHR(x,3)
#define Sig1(x) ROTR(x,17)^ROTR(x,19)^SHR(x,10)





int main(int argc, char *argv[]){

    WORD x = 0xF1234567;
    WORD y = 0x0A0A0A0A;
    WORD z = 0xB0B0B0B0;

    WORD ans; 
    ans = CH(x,y,z);

    printf("CH(%08" PF ",%08" PF ",%08" PF ")= %08" PF "\n", x,y,z,ans);
    ans = MAJ(x,y,z);
    printf("MAJ(%08" PF ",%08" PF ",%08" PF ")= %08" PF "\n", x,y,z,ans);

    printf("ROTL(%08" PF " -> %08" PF "\n", x, ROTL(x,4));
    printf("ROTR(%08" PF " -> %08" PF "\n", x, ROTR(x,4));

    printf("SHR(%08" PF " -> %08" PF "\n", x, SHR(x,4));
    printf("SIG0(%08" PF " -> %08" PF "\n", x, SIG0(x));
    printf("SIG1(%08" PF " -> %08" PF "\n", x, SIG1(x));
    printf("Sig0(%08" PF " -> %08" PF "\n", x, Sig0(x));
    printf("Sig1(%08" PF " -> %08" PF "\n", x, Sig1(x));

    return 0;
}