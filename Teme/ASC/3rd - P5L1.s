.data
n: .word 6
v: .word 25,18,10,0,-4,3

#5. Program care sorteaza un vector de numere.

.text					#sortare bubble sort
main:
	lw $t0,n			#n si contor
	la $s0,v			#adresa v
	add $s5,$zero,$zero	#contor care ramane 0 daca nu se face nici o permutare
		
comp:
	lw $t1,0($s0)		#primul element
	add $s0,$s0,4
	lw $t2,0($s0)		#al doilea
	sub $s0,$s0,4
	bgt $t1,$t2,swap	#compar si le schimb daca e cazul
	
cont:
	add $s0,$s0,4		#pregatesc urmatoarea pereche
	sub $t0,$t0,1		#scad contorul
	bne $t0,1,comp		#daca nu i-am comparat pe toti, revin
	
	
	bne $s5,0,main		#ma intorc in main ca sa reinitializez atat valoarea contorului 
						#cat si adresa de inceput al vectorului
	j end				#daca in schimb s5 e 0 inseamna ca vectorul e sortat 
						#deci programul e terminat
	
swap:	
	sw $t2,0($s0)	
	add $s0,$s0,4
	sw $t1,0($s0)
	sub $s0,$s0,4
	add $s5,$s5,1		#daca am apucat sa fac o sortare nu-i garantat ca vectorul
	j cont				#e ordonat
	
end:
	li $v0,10
	syscall