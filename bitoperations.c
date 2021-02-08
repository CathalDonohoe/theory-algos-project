#include <stdio.h>

void bin_print(unsigned int i){
    // Number of bits in an Integer
    int j = sizeof(unsigned int) * 8;

    //Temporary Variable
    int k;

    // Loop over the number of bits in i.
    for(j--;j>=0;j--){
        //
        k = ((1<< j) & i)? 1 : 0;
        //print k
        printf("%d", k);
    }
}

// Standard main structure
int main(int argc, char *argv[]){
    // Set i to a literal value
    unsigned int i = 4294967295;//1; // 0xf1; // 241 // 8589934591

    // whaty we're printing
    printf("Original:   ");
    // print i in binary
    bin_print(i);
    // end line
    printf("\t%x\t%u\n", i, i);

    for(int j = 0; j < 40; j++){
        //what the operation is
        printf("%3u << %2d: ", i, j);
        // i shifted left j times
        bin_print(i << j);
        //end line
        printf("\n");
    }

    //evertring is okay
    return 0;
}