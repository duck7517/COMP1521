main:
    li   $v0, 5         #   scanf("%d", &x);
    syscall             #
    move $t0, $v0
    li   $t1, 0         #   i = 0
    li   $t2, 0         #   j = 0

loop_columns:
    bge  $t1, $t0, end_columns

    li   $a0, '*'       #   printf("%d\n", '*');
    li   $v0, 11
    syscall
    
    
    addi $t1, $t1, 1    #   i++
    j    loop_columns
    
end_columns:
    li   $t1, 0         #   i = 0
    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall
    addi $t2, $t2, 1    #   j++
    blt  $t2, $t0, loop_columns


end:

    li   $v0, 0         # return 0
    jr   $ra
