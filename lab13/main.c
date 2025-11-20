#include <stdio.h>

typedef int (*funcp) (int x);

int main(void){
unsigned char codigo[]={0x83, 0xC7, 0x01, // add $0x1,%edi
                            0x89, 0xF8,       // mov %edi,%eax
                            0xC9,             // leave
                            0xC3};            // ret

    int i;
    funcp f;
    f=(funcp) codigo;
    i=(*f)(10);
    printf("'i' é igual a= %d\n", i);
    return 0;
}