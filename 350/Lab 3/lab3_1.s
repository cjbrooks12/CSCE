.data # "data section" global, static modifiable data
yes:   .asciiz " is a multiple of 2\n"
no:	   .asciiz " is not a multiple of 2\n"
.text    # "text section" code and read-only data
.globl main # declare `main' as a global symbol

main:
	addi	$t0, $0, 128	
	
	addi	$t1, $t0, -1
	and 	$t2, $t0, $t1
	beq		$t2, $0, YES
	bne		$t2, $0, NO
	
YES:
	add $a0, $0, $t0
    li $v0, 1 # "print int" system call
    syscall
        
	la $a0, yes
    li $v0, 4
    syscall

	addi	$v0, $0, 10
	syscall
	
NO:
	add $a0, $0, $t0
    li $v0, 1 # "print int" system call
    syscall
        
	la $a0, no
    li $v0, 4
    syscall

	addi	$v0, $0, 10
	syscall
