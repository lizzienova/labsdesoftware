unsigned char switch_byte(unsigned char x)
{
    unsigned char prim=(x&0xF0)>>4;
    unsigned char seg=(x&0x0F)<<4;
    return prim | seg;
}

int main()
{
    unsigned char x=0xAB;
    unsigned char y=switch_byte(x);
    printf("0x%X\n", y);
    return 0;
}