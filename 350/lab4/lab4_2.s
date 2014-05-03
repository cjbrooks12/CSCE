.data
.align 2

# Declaration of original matrix A
A0:			.word 41, 42, 43, 44
A1:			.word 55, 56, 57, 58
A2:			.word 19, 10, 11, 12
A3:			.word 23, 24, 25, 26
A:			.word A0, A1, A2, A3

NUMROWS_A:	.word	4
NUMCOLS_A:	.word	4

# Declaration of transposed matrix t
T0:			.word  0,  0,  0,  0
T1:			.word  0,  0,  0,  0
T2:			.word  0,  0,  0,  0
T3:			.word  0,  0,  0,  0
T:			.word T0, T1, T2, T3

NUMROWS_T:	.word	4
NUMCOLS_T:	.word	4

COMMA: 		.asciiz ", "
NL:			.asciiz "\n"
SPACE:		.asciiz " "
MAT_A:		.asciiz "Matrix A\n"
MAT_T:		.asciiz "Matrix T\n"
.text
.globl	main

#void mat_transpose(int **A, int **T, int NUMROWS_A, int NUMCOLS_A) {
#   int i, j;
#
#   for ( i = 0; i < NUMROWS_A; ++i ) {
#       for ( j = 0; j < NUMCOLS_A; ++j ) { 
#           T[j][i] = A[i][j];
#		}
#	}
#   return;
#}
	
main:
	la			$a0, A
	la 			$a1, T
	la 			$a2, NUMROWS_A
	la			$a3, NUMCOLS_A
	jal 		mat_transpose
	
	la			$a0, MAT_A	
	li			$v0, 4
	syscall
	
	la 			$a0, A
	la			$a1, NUMCOLS_A
	la			$a2, NUMROWS_A
	jal			mat_print
	
	la			$a0, NL		
	li			$v0, 4	
	syscall
	
	la			$a0, MAT_T		
	li			$v0, 4
	syscall
	
	la 			$a0, T
	la			$a1, NUMCOLS_T
	la			$a2, NUMROWS_T
	jal			mat_print
	
	li			$v0, 10
	syscall  

mat_transpose:
	move		$t0, $a0		# move address of matrix in $a0 into register $t0
	move		$v0, $a1		# move address of matrix in $a1 into register $v0 to be returned
	
	
	lw			$t4, ($a2)		# move count for number of rows to $t1
	addi		$t5, $0, 0		# set row index to $t2
	lw			$t6, ($a3)		# move count for number of columns to $t3
	addi		$t7, $0, 0		# set column index to $t4
	
trans_row:
	beq			$t5, $t4, trans_col
	
	#load value of A[i][j] and store it in $t3
	sll			$t1, $t7, 2
	add			$t1, $t1, $t0
	lw			$t3, ($t1)

	sll			$t1, $t5, 2
	add			$t2, $t3, $t1
	lw			$t3, ($t2)
	
	#get address of T[j][i] and store $t3 in it
	sll			$t1, $t5, 2
	add			$t1, $t1, $v0
	lw			$t2, ($t1)

	sll			$t1, $t7, 2
	add			$t2, $t2, $t1
	sw			$t3, ($t2)
	
	addi 		$t5, $t5, 1		# increment row counter
	
	j			trans_row
	
trans_col:
	addi 		$t7, $t7, 1		# incrememnt column counter
	bge			$t7, $t6, exit_trans
	
	addi 		$t5, $0, 0		# reset row counter
	
	j 			trans_row

exit_trans:
	la			$a0, NL		
	li			$v0, 4			# print new line
	syscall
	jr			$ra 
	
	
	
	
	
	
# Print Matrix
#-------------------------------------------------------------------------------
mat_print:
	move		$t0, $a0		# move address of matrix in $a0 into register $t0
	
	
	lw			$t4, ($a1)		# move count for number of rows to $t1
	addi		$t5, $0, 0		# set row index to $t2
	lw			$t6, ($a2)		# move count for number of columns to $t3
	addi		$t7, $0, 0		# set column index to $t4
	
loop_row:
	beq			$t5, $t4, loop_col # if row counter is equal to length of row, go to next row
	
	sll			$t1, $t7, 2		# Shift left twice (same as i * 4)
	add			$t2, $t1, $t0	# Address of pointer A[i]
	lw			$t3, ($t2)		# Get address of an array A[i] and put it into register $t3

	sll			$t1, $t5, 2		# Shift left twice (same as j * 4)
	add			$t2, $t3, $t1	# Address of A[i][j]
	lw			$t3, ($t2)		# Load value of A[i][j]
	
	move 		$a0, $t3	
	li			$v0, 1			# print number
	syscall
	
	la			$a0, SPACE		
	li			$v0, 4			# print space
	syscall
	
	addi 		$t5, $t5, 1		# increment counter
	
	j			loop_row
	
loop_col:
	addi 		$t7, $t7, 1		# incrememnt column counter
	bge			$t7, $t6, exit_print	# if column counter is equal to number of columns, return 
	
	la			$a0, NL		
	li			$v0, 4			# print new line
	syscall
	
	addi 		$t5, $0, 0		# reset row counter
	
	j 			loop_row

exit_print:
	la			$a0, NL		
	li			$v0, 4			# print new line
	syscall
	jr			$ra 
	
	
	
	
	
	
	