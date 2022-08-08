# read an integer
# print 1 iff  the least significant bit is equal to the most significant bit
# print 0 otherwise

main:
    li   $v0, 5
    syscall


    # THESE LINES JUST PRINT 42
    # REPLACE THE LINES BELOW WITH YOUR CODE
    move $t0, $v0
    
    
    li   $t1, 1         #bottom mask = 1
    
    li   $t2, 1    
    sll  $t2, $t2, 31   #topmask

    and  $t3, $t1, $t0  #bottom bit
    
    blt  $t0, 0, negative
    
    and  $t4, $t2, $t0  #top bit
    
    beq  $t3, $t4, print_equal
    b    print_unequal
    
negative: 
    beq  $t3, 1, print_equal
    b    print_unequal
    
print_unequal:
    li $a0, 0
    li $v0, 1
    syscall
    li   $a0, '\n'
    li   $v0, 11
    syscall
    
    b    end
    
print_equal:
    li $a0, 1
    li $v0, 1
    syscall
    li   $a0, '\n'
    li   $v0, 11
    syscall
    
    b    end

end:
    li $v0, 0
    jr $31
