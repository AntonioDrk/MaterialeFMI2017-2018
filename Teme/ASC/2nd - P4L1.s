.data
x: .word 5
n: .word 6
v: .word 3,7,9,16,5,24
y: .space 4

#4. Program care cauta un numar x intr-un vector de numere si pune in y
#	  valoarea 1/0 dupa cum x apare/nu apare in vector.

.text
main:
	lw $t0,n	#nr de elemente, folosit ca si contor
	lw $t1,x	#elementul de comparat
	la $s0,v	#adresa de inceput a vectorului
	
sarci:
	beq $t0,0,nope	#daca contorul e 0, nu s-a gasit
	lw $t2,0($s0)	#incarc element din vector
	beq $t1,$t2,gud	#daca am gasit, e bine
	add $s0,$s0,4	#pregatesc memoria pentru elementul urmator
	sub $t0,$t0,1	#scad contorul
	j sarci			#reincep ciclul
	
gud:
	li $v0,1
	sb $v0,y			#am gasit, deci pun 1
	j exit
	
nope:
	li $v0,0
	sb $v0,y			#n-am gasit, deci pun 0

exit:
	syscall