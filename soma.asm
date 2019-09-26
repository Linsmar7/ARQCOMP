#ALUNO: LINSMAR DA SILVA VITAL
#ARQCOMP 2019.2
				#SOMA
				
.data
z:	.float 1.34
if:	.float 6.5
ttl:	.float
first:	.asciiz "Informe o primeiro numero: "
secnd:	.asciiz "Informe o segundo numero: "
res:	.asciiz "Soma: "
error:	.asciiz "Resultado descartado! "

.text   
.globl  main            	
        
main:
li $v0, 4	#codigo syscall pra 'cout' uma string
la $a0, first	#endereço de 'first'
syscall		#'cout' a string

#pega o primeiro número do usuário e coloca em $f1
li $v0, 6
syscall
mov.s $f1, $f0

li $v0, 4
la $a0, secnd
syscall

#pega o segundo número do usuário e coloca em $f2
li $v0, 6
syscall
mov.s $f2, $f0

add.s   $f3, $f1, $f2	#faz a soma e coloca em $f3

l.s $f4, z	#botando 'z' em $f4
mul.s $f5, $f3, $f4	#multiplicando a soma com o 'z' e  colocando em $f5

l.s $f6, if	#colocando o 'if' em $f6

#se $f5 (soma coma a multiplicação) > $f4 (z), 'then'
c.lt.s 1, $f6, $f5
bc1t 1, then
#se não, isso acontece:
li $v0, 4	#codigo pra printar string
la $a0, error
syscall
j FINAL

then:
li $v0, 4	#codigo pra printar string
la $a0, res
syscall
mov.s $f12, $f5
li $v0, 2
syscall

FINAL:
li, $v0, 10
syscall

