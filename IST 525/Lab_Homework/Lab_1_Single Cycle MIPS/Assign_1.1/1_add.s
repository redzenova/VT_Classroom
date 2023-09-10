.data

     text:  .asciiz "Enter a number: "
     text1: .asciiz "TRUE"

.text

 main:
    # Printing out the text
    li $v0, 4
    la $a0, text
    syscall

    # Getting user input
    li $v0, 5
    syscall

    # Moving the integer input to another register
    move $t0, $v0

    # Printing out the text
    li $v0, 4
    la $a0, text
    syscall

    # Getting user input
    li $v0, 5
    syscall

    # Moving the integer input to another register
    move $t1, $v0


    add $t2,$t0,$t1

    li $v0, 1
    move $a0,$t2
    syscall

    li $v0,10
    syscall