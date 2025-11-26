
.data
  s1: .string "ls -ls"

  .text
  .globl main
  .extern system
  main:

    pushq %rbp
    movq  %rsp, %rbp


    movq $s1, %rdi
    call system
    xorl %eax, %eax


    leave
    ret
