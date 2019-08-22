.data
A: .word 40		# declaracao de variavel inteiro (word)
B: .word 37
C: .word 0

.text   
.globl  main            
        
main:   
la $t0, A		# load address - carrega endereço de A em $t0
la $t1, B
la $t2, C

lw $t0,0($t0)	        # load word - lê valor de A para $t0
lw $t1,0($t1)

add $t3, $t0, $t1	# $t3 = $t0 + $t1
sw $t3, 0($t2) 		# $t2 = $t3

#Finalização
li $v0, 10	   	#chamada de sistema pra encerar
syscall