# read a line and print whether it is a palindrome

main:
    la   $a0, str0       # printf("Enter a line of input: ");
    li   $v0, 4
    syscall

    la   $a0, line
    la   $a1, 256
    li   $v0, 8          # fgets(buffer, 256, stdin)
    syscall              #
    
    li   $t0, 0          # i = 0
    
count_line:
    la   $t1, line
    add  $t1, $t1, $t0
    lb   $t2, ($t1)
    beq  $t2, 0, count_end
    addi $t0, $t0, 1
    b    count_line

count_end:
    sub  $t0, $t0, 2    # k = i - 2
    li   $t1, 0         # j = 0
    la   $t2, line

check_palindrome:
    bge  $t1, $t0, is_palindrome
    
    add  $t3, $t2, $t0
    add  $t4, $t2, $t1
    lb   $t5, ($t3)
    lb   $t6, ($t4)
    
    addi $t1, $t1, 1    # j++
    sub  $t0, $t0, 1    # k--
    beq  $t5, $t6, check_palindrome
    b    isnt_palindrome

isnt_palindrome:
    la   $a0, not_palindrome
    li   $v0, 4
    syscall
    b    end

is_palindrome:
    la   $a0, palindrome
    li   $v0, 4
    syscall
    b    end
end:
    li   $v0, 0          # return 0
    jr   $ra


.data
str0:
    .asciiz "Enter a line of input: "
palindrome:
    .asciiz "palindrome\n"
not_palindrome:
    .asciiz "not palindrome\n"


# line of input stored here
line:
    .space 256

