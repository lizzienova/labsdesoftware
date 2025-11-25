#include <stdio.h>

//a
unsigned char switch_byte (unsigned char x) {
    unsigned char y = x<<4;    
    unsigned char z = x>>4;  
    unsigned char resp = y|z;
    return resp;
}

unsigned char rotate_left (unsigned char x, int n) {
    unsigned char y = x<<n;
    unsigned char z = x>>(8-n);
    unsigned char resp = y|z;
    return resp;
}


int main()
{
    unsigned char a = 0x61;
    unsigned char b = rotate_left(a,1);
    unsigned char c = rotate_left(a,2);
    unsigned char d = rotate_left(a,7);
    printf("%02x\n", b);
    printf("%02x\n", c);
    printf("%02x\n", d);
    printf("switch_byte(0xAB) = 0x%02X\n", switch_byte(0xAB));
    printf("switch_byte(0x3C) = 0x%02X\n", switch_byte(0x3C));
    return 0;
}