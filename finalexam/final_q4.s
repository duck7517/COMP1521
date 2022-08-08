# read 10 numbers into an array

main:

    li   $t0, 0          # i = 0
loop0:
    bge  $t0, 10, end0   # while (i < 10) {

    li   $v0, 5          #   scanf("%d", &numbers[i]);
    syscall              #

    mul  $t1, $t0, 4     #   calculate &numbers[i]
    la   $t2, numbers    #
    add  $t3, $t1, $t2   #
    sw   $v0, ($t3)      #   store entered number in array

    add  $t0, $t0, 1     #   i++;
    b    loop0           # }
    
end0:
    
    li   $t0, 0          # i = 0
    
print_positive_loop_body:
    bge  $t0, 10, print_positive_loop_end   # while (i < 10) {

    mul  $t1, $t0, 4     #   calculate &numbers[i]
    la   $t2, numbers    #
    add  $t3, $t1, $t2
    lw   $t4, ($t3)
    
    bgt  $t4, 0, print_positive
    
    add  $t0, $t0, 1     #   i++;
    b    print_positive_loop_body      # }
    
print_positive_loop_end:
    li   $a0, '\n'
    li   $v0, 11
    syscall
    
    li   $t0, 0          # i = 0
    b    print_negative_loop_body
    
print_positive:
    move $a0, $t4
    li   $v0, 1
    syscall 
    
    li   $a0, ' '
    li   $v0, 11
    syscall
    
    add  $t0, $t0, 1
    b    print_positive_loop_body

print_negative_loop_body:
    bge  $t0, 10, print_negative_loop_end   # while (i < 10) {

    mul  $t1, $t0, 4     #   calculate &numbers[i]
    la   $t2, numbers    #
    add  $t3, $t1, $t2
    lw   $t4, ($t3)
    
    blt  $t4, 0, print_negative
    
    add  $t0, $t0, 1     #   i++;
    b    print_negative_loop_body      # }
    
print_negative_loop_end:
    li   $a0, '\n'
    li   $v0, 11
    syscall
    add  $t0, $t0, 1
    b    end
    
print_negative:
    move $a0, $t4
    li   $v0, 1
    syscall
    
    li   $a0, ' '
    li   $v0, 11
    syscall
    
    add  $t0, $t0, 1
    b    print_negative_loop_body

end:
    li   $v0, 0
    jr   $31             # return

.data

numbers:
    .word 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  # int numbers[10] = {0};
