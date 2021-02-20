#include <stdio.h>

void bin_print(unsigned int i){
    // Number of bits in an Integer
    int j = sizeof(unsigned int) * 8;

    //Temporary Variable
    int k;

    // Loop over the number of bits in i.
    for(j--; j >= 0; j--){
        // pick out the j^th bit of i, left to right
        k = ((1<< j) & i) ? 1 : 0;
        //print k
        printf("%d", k);
    }
}

// Standard main structure
int main(int argc, char const *argv[]){

    printf("%d\n", argc);
    return 0;
    

    // Set i to a literal value
    unsigned int i = 0x0f0f0f0f;//1; // 0xf1; // 241 // 8589934591

    // whaty we're printing
    printf("Original:\t");
    // print i in binary
    bin_print(i);
    // end line
    printf("\t%x\t%u\n\n", i, i);

    //32
    int j = sizeof(unsigned int) * 8;

    for(j--; j >= 0; j--){
        // i shifted left j times
        bin_print(1 << j); printf("\n");
        //i
        bin_print(i); printf("\n");
        printf("-------------------------- &\n");
        // (1 shifted left j times) bitwise logical and i.
        bin_print((1 << j) & i); printf("\n\n");
    }

    //evertring is okay
    return 0;
}