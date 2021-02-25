#include <stdio.h>
#include <inttypes.h>


uint32_t Ch(uint32_t x, uint32_t y, uint32_t z){
    return (x&y)^(~x&z);
}



int main(int argc, char *argv[]){

    uint32_t x = 0xf0f0f0f0;
    uint32_t y = 0xf0f0f0f0;
    uint32_t z = 0xf0f0f0f0;

    return 0;
}