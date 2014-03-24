.data
prompt:	.asciiz	"Enter your Message: "	
str:	.space 100			# Reserve 100 bytes
msg:	.asciiz	"strlen() returns: "

.text
main:							# Start of your Code
	la			$a0, prompt		# Load address of the message to prompt
	li			$v0, 4			# "print string" system call
	syscall
	
	la			$a0, str		# Load address of the reserved space
	addi			$a1, $0, 101		# Load the value of the amount of the reserved space plus 1
	
	li			$v0, 8			# "read string" system call
	syscall
	
	jal	strlen					# Call your strlen() function
	add			$t0, $v0, $0	# Save the return value to register 
	
	la			$a0, msg		# Load address of the message
	li			$v0, 4			# "print string" system call
	syscall
	
	add			$a0, $t0, $0	# Copy the return value to register $a0
	li			$v0, 1			# "print integer" system call
	syscall						
	
	addi		$v0, $0, 10		# Move "exit" system function code to argument reg
	syscall						# Request the OS to carry out the program exit
	
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
	
	


