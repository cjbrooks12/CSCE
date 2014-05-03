.data
B:	.word 722		# B[0]
	.word 21 		# B[1]
	.word 4 		# B[2]
	.word 89		# B[3]
	.word 16384		# B[4]
	.word 350		# B[5]
	.word 6046		# B[6]
	.word 897		# B[7]
	.word 1201		# B[8]
	.word 0			# B[9]
	.word 904		# B[10]
	.word 897		# B[11]
	.word 4805		# B[12]
	.word 679		# B[13]
	.word 7			# B[14]
SZ:	.word 15
space: .asciiz " "
.text

#int i, j, tmp;
#
#   for (i=0; i<SZ; ++i) {
#       for (j=i+1; j<SZ; ++j) {
#           if (B[i] > B[j]) {
#               tmp = B[i];
#               B[i] = B[j];
#               B[j] = tmp;
#           }
#       }
#       
#       /* Optional: Use this to display */
#       printf("B[%d] = %d\n", i, B[i]);
#   }


main:
	addi 	$t0, $0, 0 #t0 will be i
	addi 	$t1, $0, 0 #t1 will be j
	addi 	$t2, $0, 0 #t2 will be temp
	la 		$a0, SZ

	jal		LOOPI
	j		PRINT
	
LOOPI:
	jal 	LOOPJ 
	addi	$t0, $t0, 1
	blt		$t0, $s0, LOOPI	

LOOPJ:
	mul 	$s0, $t0, 4
	mul		$s1, $t1, 4
	lw		$s2, 0($a0)
	lw		$s3, 4($a0)
	
	bgt		$s2, $s3, SWAP	
	
	addi	$t1, $t1, 1
	blt		$t1, $s0, LOOPJ
	
SWAP:
	sw		$t2, 0($s0)
	sw		$a0, 0($s3)
	sw		$a0, 4($s2)
	
PRINT:
	lw 		$a0, 0($t0)
	li 		$v0, 1
	syscall

	addi 	$t0, $t0, 4
	addi 	$t1, $t1, 1
	slt 	$t2, $s0, $t1
	beq 	$t2, $zero, PRINT
	
	j		EXIT
	

EXIT:
	li	$v0, 10
	syscall
