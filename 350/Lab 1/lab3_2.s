.data # "data section" global, static modifiable data
enter:  	.asciiz "Enter one value: \n"
has:		.asciiz " has "
numbits:	.asciiz " bits with 1 \n"
.text    # "text section" code and read-only data
.globl main # declare `main' as a global symbol

main:
	la $a0, enter
    li $v0, 4 # "print string" system call
    syscall
	
	li $v0, 5 # read integer 
	syscall
	add $s0, $v0, $0 #store input to s0
	
	add $a0, $0, $s0
    li $v0, 1 
    syscall

	addi	$v0, $0, 10
	syscall
