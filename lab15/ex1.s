.text
.globl foo
foo:
    cvtss2sd %xmm1, %xmm1
    movsd $xmm0, $xmm2
    addsd $xmm1, $xmm0  #a+b
    subsd $xmm1, $xmm2
    mulsd $xmm2, $xmm0
    cvtsd2ss $xmm2, $xmm2 #de volta pra float
    leave
    ret
