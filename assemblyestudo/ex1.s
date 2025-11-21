/*
int max_of_two(int x, int y) {
    if (x > y) {
        return x;
    } else {
        return y;
    }
}
*/

.text
.globl max_of_two
max_of_two:
    cmp %esi, %edi
    jle returny
    movl %edi, %eax
    ret

returny:
    movl %esi, %eax
    ret