.data
pi:	.float	3.14159
first: .asciiz "Digite o valor do raio do circulo, e ENTER\n"
second: .asciiz "Raio digitado e' "
third: .asciiz "Area do circulo com raio "
cont: .asciiz " e' "
end: .asciiz "\n"

.text   
.globl  main            
        
main:
#colocando pi em $f10
l.s $f10, pi

li $v0, 4	#codigo syscall pra 'cout' uma string
la $a0, first	#endereço de 'first'
syscall		#'cout' a string

#$f1 = raio
li $v0, 6
syscall
mov.s $f1, $f0

#'cout' na segunda string
li $v0, 4
la $a0, second
syscall

#'cout' no radio digitado pelo usuario
mov.s $f12, $f1
li $v0, 2
syscall

#quebra de linha
li $v0, 4
la $a0, end
syscall

mul.s $f2, $f1, $f1	#multiplicando o raio por ele mesmo
mul.s $f3, $f2, $f10	#multiplicando o resultado da operaçao acima com pi

#'cout' na terceira string
li $v0, 4
la $a0, third
syscall
#'cout' no raio digitado pelo usuario
mov.s $f12, $f1
li $v0, 2
syscall
#continuacao da string
li $v0, 4
la $a0, cont
syscall
#'cout' no resultado final da operaçao
mov.s $f12, $f3
li $v0, 2
syscall
#quebra de linha
li $v0, 4
la $a0, end
syscall

#FINAL
li $v0, 10
syscall


