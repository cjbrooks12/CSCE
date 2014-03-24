.data # "data section" global, static modifiable data
enter:  	.asciiz "Enter one value: \n"
has:		.asciiz " has "
numbits:	.asciiz " bit(s) with 1 \n"
.text    # "text section" code and read-only data
.globl main # declare `main' as a global symbol

main:
	addi	$t0, $0, 0 #set global counter to 0
	addi 	$t1, $0, 32 #set loop counter to 32
	addi 	$t7, $0, 1 # $t7 is 1, because it is used frequently

	la 		$a0, enter
    li 		$v0, 4
    syscall
	
	li 		$v0, 5 # read integer from keyboard
	syscall
	add		$s0, $v0, $0 #store input to s0
	add		$t6, $s0, $0 #store input to s0
	j 		LOOP
	
ADDCOUNT:
	addi 	$t0, $t0, 1
	j 		LOOP
		
LOOP: 
	beq		$t1, $0, EXIT
	and 	$s1, $s0, $t7 #if s0 AND 1 == 1, last bit is 1. If it is anything else, it must be zero
	srl		$s0, $s0, 1 #shift, prepare to test next bit
	addi 	$t1, $t1, -1 #decrement loop counter
	beq		$s1, $t7, ADDCOUNT 
	bne 	$t1, $t7, LOOP #when loop counter hits zero, terminate
	
EXIT:
	add $a0, $0, $t6
    li $v0, 1
    syscall

	la $a0, has
    li $v0, 4 
    syscall

	add $a0, $0, $t0
    li $v0, 1
    syscall
    
    la $a0, numbits
    li $v0, 4 
    syscall

	addi	$v0, $0, 10
	syscall
	

	
