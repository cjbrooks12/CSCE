        .data
msg1:   .asciiz  "The sum is "
NL:     .asciiz  "\n"
A:      .word    3
B:      .word    10
C:      .word    20

        .text
        .globl  main		# main is a global symbol

main:
		la		$a0, A
		lw		$a0, 0($a0)
		
		la		$a1, B
		lw		$a1, 0($a1)

		la		$a2, C
		lw		$a2, 0($a2)

		jal 	SUM
		move 	$t0, $v0

		li       $v0, 4
		la       $a0, msg1
		syscall                 # print "The sum is "

		li		$v0, 1
		move	$a0, $t0		# move sum to $a0
		syscall                	# print the sum

		li		$v0, 4
		la		$a0, NL
		syscall                 # print newline

		li       $v0, 10
		syscall                 # exit

SUM:
		add 	$t0, $a0, $a1
		add 	$v0, $t0, $a2
		jr 		$ra

	
