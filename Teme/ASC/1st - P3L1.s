.data 
n: .word 5
v: .word 3,4,15,18,20
s: .space 4


#3. Program care calculeaza suma elementelor unui vector de numere.
.text
main:
	lw $t0,n	#numarul de elemente
	la $t1,v	#adresa vectorului
	li $s1,0	#suma
start:
	beq $t0,0,fin		#daca n a ajuns la 0, sari la final
	lw $t2,0($t1)		#incarc in t2 valoarea *t1[s0] (sau v[s0])
	add $s1,$s1,$t2		#suma
	add $t1,$t1,4		#pregatesc adresa urmmatorului element al vectorului
	sub $t0,$t0,1		#scad contorul
	j start
	
fin:
	sw $s1,s
	li $v0,10
	syscall
	