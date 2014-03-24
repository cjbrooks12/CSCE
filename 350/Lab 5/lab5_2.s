.data
prompt:	.asciiz	"Enter your Message: "	
str:	.space 100			# Reserve 100 bytes
msg:	.asciiz	"atoi() returns: "

.text
main:
	la		$a0, prompt	
	li		$v0, 4
	syscall
	
	la		$a0, str
	addi	$a1, $0, 101
	
	li		$v0, 8
	syscall
	
	jal		atoi			
	add		$t7, $v0, $0		
	
	la		$a0, msg		# Load address of the message
	li		$v0, 4			# "print string" system call
	syscall
	
	add		$a0, $t7, $0	# Copy the return value to register $a0
	li		$v0, 1			# "print integer" system call
	syscall						
	
	addi		$v0, $0, 10		# Move "exit" system function code to argument reg
	syscall					# Request the OS to carry out the program exit

	# strlen function
#-------------------------------------------------------------------------------
#throughout whole function, $t0 will always hold the char and $t1 is the position counter

atoi:	
	lb			$t0, 0($a0)
	li 			$t1, 0			#length counter	
	li 			$t2, 48
	li			$t3, 57
loop_get_numbers:
	lb			$t0, 0($a0)		# load char to test if it is a number
	blt 		$t0, $t2, get_value	
	bgt			$t0, $t3, get_value 
	addi 		$a0, $a0, 1 	# increment the string pointer
	addi 		$t1, $t1, 1		# increment length of counter
	j			loop_get_numbers
get_value:
	sub			$a0, $a0, $t1	# restore pointer to beginning of string
	add 		$v0, $0, $0		# initialize return value to be zero to return sum
	add 		$t2, $0, $0 
	add 		$t3, $0, $0 	# initialize $t4, which will hold the the int to be multiplied
	addi 		$t4, $0, 10 	# initialize #t5 which will multiple each number by 10 iteratively
sum_loop:
	add 		$v0, $v0, $t2 	# add position value to total sum in $v0
	ble			$t1, $0, exit
	lb			$t0, 0($a0)		# get a character to test value of
	addi 		$t2, $t0, -48	# move char to $t2
	addi 		$t1, $t1, -1 	# decrease position counter 
	add 		$t3, $t1, $0 	# move position number to $t3
	addi 		$a0, $a0, 1 	# go to next char
	j 	 		exponential 	#calculate exponential 10^$t3
exponential:
	addi		$t3, $t3, -1 	# keep track of how many times the loop is run
	blt			$t3, $0, sum_loop
	mul 		$t2, $t2, $t4	# each loop multiplies the number by 10, for a total of 10^pos
	j exponential
exit:
	jr			$ra
