    .text
    .globl _start
_start:
    movabs $0xCCCCCCCCCCCCCCCC, %rdi

    mov $6, %eax
    xor %rcx, %rcx
hw_loop:
    mov %eax, (%rdi,%rcx,1)
    add $400, %rcx
    cmp $3600, %rcx
    jl hw_loop

    mov $7, %eax
    mov $3600, %rcx
lab_loop:
    mov %eax, (%rdi,%rcx,1)
    add $400, %rcx
    cmp $7600, %rcx
    jl lab_loop

    mov $59, %eax
    mov $7600, %rcx
prj_loop:
    mov %eax, (%rdi,%rcx,1)
    add $400, %rcx
    cmp $9200, %rcx
    jl prj_loop

    mov $61, %eax
    mov %eax, 9200(%rdi)
    mov %eax, 9600(%rdi)

    mov $0, %esi
    movabs $0x55, %rax
    call *%rax

    movabs $0x7c00, %rax
    jmp *%rax
