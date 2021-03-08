#include <stdio.h>
#include <inttypes.h>


#define BYTE uint8_t


int main(int argc, char *argv[]){
    BYTE b;

    FILE *f;

    f= fopen(argv[1], "r");

    size_t nobytes;

    nobytes = fread(&b, 1, 1, f);
    printf("%c", b);
    while ( nobytes)
    {
        nobytes = fread(&b, 1, 1, f);
        printf("%c", b);
    }

    fclose(f);
    printf("\n");


    return 0;

}