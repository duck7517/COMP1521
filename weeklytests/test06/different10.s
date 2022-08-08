# x in register $t0
# i in register $t1
# n_seen in register $t2
# registers $t3 and $t4 used to hold temporary results
main:

    li   $t2, 0          # n_seen = 0;
read:
    bge  $t2, 10, end    # while (n_seen < 10) {
    la   $a0, string0    # printf("Enter a number: ");
    li   $v0, 4
    syscall
    li   $v0, 5          # scanf("%d", &x);
    syscall

    move $t0, $v0
    b    check
    
check:
    li   $t5, 0         # i = 0
check_loop:
    mul  $t3, $t5, 4    # calculate &numbers[i]
    la   $t4, numbers   #
    add  $t3, $t3, $t4  #
    lw   $t7, ($t3)     # numbers[i] = y
    
    beq  $t7, $t0, read # if x = y, end check
    addi $t5, $t5, 1    # i++;
    blt  $t5, $t2, check_loop
    
    addi $t2, $t2, 1    # n_seen++
    
    mul  $t3, $t2, 4    # calculate &numbers[n_seen]
    la   $t4, numbers   #
    add  $t3, $t3, $t4  #
    sw   $t0, ($t3)     # numbers[n_seen] = x
    
    b    read
    

end:
    
    la   $a0, string1   # printf("10th different number was: ");
    li   $v0, 4
    syscall
    
    la   $t4, numbers
    addi $t3, $t4, 40
    lw   $t0, ($t3)
    
    move $a0, $t0       # printf("%d", x)
    li   $v0, 1
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    li   $v0, 0         # return 0
    jr   $ra

    
    .data

numbers:
    .space 40           # int numbers[10];

string0:
    .asciiz "Enter a number: "
string1:
    .asciiz "10th different number was: "
