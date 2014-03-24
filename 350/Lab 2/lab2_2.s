.data 0x10008000
B:	.word 300
	.word 200
	.word 100
	.word 0
i:	.word 3
.text

main:
	la		$t1, B
	
	lw  	$t0, 0($t1)
	add		$s0, $0, $t0	#set $s0 = B[0]
	
	lw  	$t0, 4($t1)
	add		$s0, $s0, $t0	#set $s0 = B[0] + B[1]
	
	lw  	$t0, 8($t1)
	add		$s0, $s0, $t0 	#set $s0 = B[0] + B[1] + B[2]
	
	sw		$s0, 12($t1)	#store $s0 into B[3]
	lw		$t0, 12($t1)	#check that the sum is stored correctly
		
	addi	$v0, $0, 10	
	syscall
