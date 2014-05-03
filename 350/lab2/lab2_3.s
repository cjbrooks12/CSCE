.data 0x10008000
mesg: .asciiz "Enter the value for register $s0: "
.text

main:
	la 		$a0, mesg
	addi	$v0, $0, 4
	syscall
	
	addi 	$v0, $0, 5
	syscall
	
	add		$s0, $v0, $0
		
	addi	$v0, $0, 10	
	syscall
