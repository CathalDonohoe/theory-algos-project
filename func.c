#include <stdio.h>
#include <inttypes.h>

#define WORD uint32_t
#define PF PRIX32
#define CH(x,y,z) (x&y)^(~x&z)
#define MAJ(x,y,z) (x&y)^(x&z)^(y&z)





int main(int argc, char *argv[]){

    WORD x = 0x0F0F0F0F;
    WORD y = 0x0A0A0A0A;
    WORD z = 0xB0B0B0B0;

    WORD ans; 
    ans = CH(x,y,z);

    printf("CH(%08" PF ",%08" PF ",%08" PF ")= %08" PF "\n", x,y,z,ans);
    ans = MAJ(x,y,z);
    printf("MAJ(%08" PF ",%08" PF ",%08" PF ")= %08" PF "\n", x,y,z,ans);
    return 0;
}