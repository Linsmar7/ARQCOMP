.data
f: .word 0
g: .word 3
h: .word 4
i: .word 2
j: .word 1

.text
.globl main

main:
la $s0, f
la $s1, g
la $s2, h
la $s3, i
la $s4, j

lw $s1, 0($s1)	# carrega valor de g ($s1) em $s1
lw $s2, 0($s2)	# h
lw $s3, 0($s3)	# i
lw $s4, 0($s4)	# j

# if (i == j)
beq $s3, $s4, entao
# else
sub $t0, $s1, $s2	# subtrair
sw $t0, 0($s0)	# store
# jump
j saida

# Finalização
entao:
add $t0, $s1, $s2
sw $t0, 0($s0)

saida:
li $v0, 10
syscall
