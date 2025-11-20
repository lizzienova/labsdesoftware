/* 
int foo (int x) {
  return add(x);
}
*/

foo:
    jmp add
    leave
    ret

