#include <stdio.h>

int main(int argc, char *argv[]){
    
    int i = 0xF1;

    printf("Dec: %d\n", i);
    printf("Hex: %x\n", i);
    printf("Size of int: %d\n", sizeof(i));
    printf("Size of int: %d\n", sizeof(char));
    

    char c = 41;
    printf("c in char is: %c\n", c);
    printf("c in int is: %d\n", c);

    int j = 1000000000;
    printf("j in char is: %c\n", j);
    printf("j in int is: %d\n", j);


    return 0;
}