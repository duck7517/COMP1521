main:
    li   $v0, 5         #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

    li   $v0, 5         #   scanf("%d", &y);
    syscall             #
    move $t1, $v0
    
    addi $t2, $t0, 1

print_loop:
    bge  $t2, $t1, end
    
    beq  $t2, 13, skip13
    
    move $a0, $t2       #   printf("%d\n", i);
    li   $v0, 1
    syscall
    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall
    
    addi $t2, $t2, 1
    j    print_loop

skip13:
    addi $t2, $t2, 1
    j    print_loop
    
end:

    li   $v0, 0         # return 0
    jr   $ra
