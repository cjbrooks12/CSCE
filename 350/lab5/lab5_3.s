.data
prompt:	.asciiz	"Enter your Message: "	
str:	.space 100			# Reserve 100 bytes
msg2:	.asciiz	"reversed string: "

.text
main:			
# Get an input string and store in $t7, with length in $t6
	la			$a0, prompt
	li			$v0, 4		
	syscall
	
	la			$a0, str	
	addi		$a1, $0, 101	
	
	li			$v0, 8			
	syscall

	add 		$t7, $a0, $0

	la			$a0, msg2		
	li			$v0, 4			
	syscall

	jal			strlen	

	add 		$t6, $v0, $0

	add 		$a0, $t6, $0
	add 		$a1, $t7, $0
		
	jal			reverse						
	
	add			$a0, $v0, $0		
	li			$v0, 4			
	syscall						
	
	addi		$v0, $0, 10		
	syscall					
	
# strlen function
#-------------------------------------------------------------------------------
strlen:	
	lb			$t1, 0($a0)
	li 			$t2, 0			#length counter	
loop:
	lb			$t1, 0($a0)
	beq 		$t1, $0, exit
	addi 		$a0, $a0, 1 	# increment the string pointer
	addi 		$t2, $t2, 1		# increment length of counter
	j			loop

exit:
	addi		$v0, $t2, -1
	jr			$ra

# reverse string function
#-------------------------------------------------------------------------------
reverse:	
# length of string is in $a0, string is in $a1
	add 		$t0, $a0, $0 	# set $t0 to the size of the string
	sub 		$sp, $sp, $t0 	#reserve space on stack to push on chars
loop_reverse:
	lb			$t1, 0($a1)		# get next char from $a1 
	beq 		$t1, $0, restore
	#push char on stack
	sb			$t1, 0($sp)		# put char from $a1 on stack
	addi 		$sp, $sp, 1 	# increment stack pointer
	addi 		$a1, $a1, 1 	# increment the string pointer
	j			loop_reverse
restore:
	sub			$a1, $a1, $t0	# restore pointer of $a1 to beginning
loop_restore:
	blt			$t0, $0, exit_reverse
	lb			$t1, 0($sp)		# get char from last position on stack
	sb 			$t1, 0($a1)		# put char at next position in $a1
	addi		$a1, $a1, 1 	# incrememnt position of $a1
	addi		$sp, $sp, -1 	# decrement stack pointer to get previous char
	addi		$t0, $t0, -1 	# decrement counter to know when to stop restoring from stack
	j 			loop_restore
exit_reverse:
	# restore pointer to beginning of $a1 and return
	sub 		$v0, $a1, $a0
	jr			$ra