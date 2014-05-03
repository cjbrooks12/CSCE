.data
msg1:	.asciiz "Please Enter a number: "
.text
.globl main

main:
	li 			$v0, 4
	la 			$a0, msg1
	syscall 					# print prompt
	
	li 			$v0, 5
	syscall		 				
	add 		$a0, $v0, $0	# read an int from console and move to $a0

	jal 		fib 

	add 		$a0, $v0, $0
	li 			$v0, 1
	syscall						# print eventual result

	li 			$v0, 10
	syscall

fib:
	addi		$sp, $sp, -12	# save regs on stack
	sw 			$ra, 0($sp)
	sw 			$s0, 4($sp)
	sw 			$s1, 8($sp)

	add			$s0, $a0, $0	# initialize fib recursion with entered number

	addi 		$t1, $0, 2 
	blt 		$s0, $t1, return	# base case

	addi 		$a0, $s0, -1	# decrement counter to get n-1 
	jal 		fib
	add	 		$s1, $0, $v0	# fib(n-1)
	
	addi 		$a0, $s0, -2
	jal 		fib				# fib(n-2)
	
	add 		$v0, $v0, $s1	# v0 = fib(n-2)+ fin(n-1)
	
	
exit:

	lw 			$ra, 0($sp) 	# restore restore from stack
	lw 			$s0, 4($sp)
	lw 			$s1, 8($sp)
	addi 		$sp, $sp, 12	# restore stack pointer
	jr 			$ra

return:
	li 			$v0, 1
	j 			exit