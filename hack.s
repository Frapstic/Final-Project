.text
.globl _start
_start:
    movabs $0x55555555e310, %rax
    movl $100, (%rax)
    leave
    ret