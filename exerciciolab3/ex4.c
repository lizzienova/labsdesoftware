unsigned char rotate_left(unsigned char x, int n)
{
    unsigned char left_shift=x<<n;
    unsigned char acerto=x>>(8-n);
    return left_shift | acerto;
}

int main()
{
    printf("0x%X\n", rotate_left(0x61, 1));
    printf("0x%X\n", rotate_left(0x61, 2));
    printf("0x%X\n", rotate_left(0x61, 7));
    return 0;
}