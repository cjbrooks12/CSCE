main:
	addi	$s1, $0, 3	
		
	add		$t0, $0, $s1
	add		$t1, $t0, $t0
	add		$t2, $t1, $t1
	add		$t3, $t2, $t2
	add		$t4, $t3, $t3
	add		$t5, $t4, $t4
	add		$t6, $t5, $t5
	add		$t7, $t6, $t6	
	
	addi	$v0, $0, 10
	syscall
