.data

     text:  .asciiz "Enter a number: "
     text2: .asciiz "The resault is: "
     newline: .asciiz "\n"

.text

 main:
    # Printing out the text "Enter a number: "
    li $v0, 4
    la $a0, text
    syscall

    # Getting user input
    li $v0, 5
    syscall

    # Moving the integer input to another register
    move $t0, $v0


    li $t1,1 # Base case
LOOP:
    # recursive case
    beq	$t0, 0, endloop	# if $t0 == 0 then endloop
    mul $t1,$t1,$t0        # $t1 = $t1 * $t0
    add $t0,$t0,-1       # $t0 = $t0 - 1
    j LOOP # jump to LOOP

endloop:
    # Printing out the text "The resault is: "
    li $v0, 4
    la $a0, text2
    syscall

    # Printing out the resault
    li $v0,1
    move $a0, $t1
    syscall

    # Printing out a new line
    li $v0, 4
    la $a0, newline
    syscall

    # Exit program
    li $v0,10
    syscall