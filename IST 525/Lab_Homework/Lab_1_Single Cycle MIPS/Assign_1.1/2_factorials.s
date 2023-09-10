.data

     text:  .asciiz "Enter a number: "

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


    li $t1,1
LOOP:
    beq	$t0, 0, endloop	# if $t0 == 0 then endloop
    mul $t1,$t1,$t0
    add $t0,$t0,-1
    j LOOP

endloop:
    li $v0,1
    move $a0, $t1
    syscall
    li $v0,10
    syscall