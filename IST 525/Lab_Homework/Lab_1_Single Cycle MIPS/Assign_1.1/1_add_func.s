.data

     text:  .asciiz "Enter a number: "
     text2: .asciiz "The sum is: "
     newline: .asciiz "\n"
     
.text

# Note:
# li = load immediate
# la = load address

# $v0 = 1 print integer
# $v0 = 4 print string
# $v0 = 5 read integer
# $v0 = 10 exit

# $a0 = address of string to print

 main:
    # Printing out the text "Enter a number: "
    li $v0, 4
    la $a0, text
    syscall

    # Getting user input number 1
    li $v0, 5
    syscall

    # Moving the integer input to another register
    move $t0, $v0

    # Printing out the text
    li $v0, 4
    la $a0, text
    syscall

    # Getting user input number 2
    li $v0, 5
    syscall

    # Moving the integer input to another register
    move $t1, $v0

     # Adding the two numbers t2 = t0 + t1
    add $t2,$t0,$t1

     # Printing out the text "The sum is: "
    li $v0, 4
    la $a0, text2
    syscall
 
     # Printing out the text t2
    li $v0, 1
    move $a0,$t2
    syscall

    # Printing out the text "\n"
    li $v0, 4
    la $a0, newline
    syscall

    # Exit
    li $v0, 10
    syscall
