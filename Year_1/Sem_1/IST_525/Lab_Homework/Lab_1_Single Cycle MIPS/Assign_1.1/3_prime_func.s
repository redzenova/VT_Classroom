# A function that takes a value n and return 0 if n is not a prime number 
#and return 1 if n is a prime number.
# Prime number : only divisible by 1 and itself ex: 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47

.data

     text:  .asciiz "Enter a number: "
     newline: .asciiz "\n"
.text
main:

# print text "Enter a number: "
li $v0, 4
la $a0, text
syscall

# read integer
li $v0,5
syscall

move $t0, $v0

li $t1,0 # int count = 0
li $t2,1 # int i = 1
LOOP:
    
    beq $t0, $t2, ENDLOOP # if t0 == t2 goto endloop
    div $t3,$t0,$t2 # t3 = t0/t2
    mfhi $t4        # t4 = t0%i  | mfhi = modulo 
    beq $t4,0,cout_1 # if t0%i == 0; cout += 1
    add $t2,$t2,1 # i+=1
    j LOOP

ENDLOOP:
    beq $t1,1,PRIME
    li $t5,0
    li $v0,1
    move $a0,$t5
    syscall
   
    # newline
    li $v0, 4
    la $a0, newline
    syscall

    # exit
    li $v0, 10
    syscall

PRIME:
    li $t5,1
    li $v0,1
    move $a0,$t5
    syscall
    
    # newline
    li $v0, 4
    la $a0, newline
    syscall

    li $v0, 10
    syscall

cout_1:
    add $t1,$t1,1
    add $t2,$t2,1
    j LOOP
