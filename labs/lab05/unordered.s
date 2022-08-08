# Read 10 numbers into an array
# print 0 if they are in non-decreasing order
# print 1 otherwise

# i in register $t0

main:

    li   $t0, 0         # i = 0

read_loop:
    bge  $t0, 10, read_end    # while (i < 10) {

    li   $v0, 5                 #   scanf("%d", &numbers[i]);
    syscall                     #

    mul  $t1, $t0, 4            #   calculate &numbers[i]
    la   $t2, numbers           #       
    add  $t3, $t1, $t2          #
    sw   $v0, ($t3)             #   store entered number in array

    addi $t0, $t0, 1            #   i++;
    j    read_loop              # }

read_end:
    
    li   $t0, 0         # i = 0
    li   $t4, 0

check_loop:
    bge  $t0, 10, ordered
    
    mul  $t1, $t0, 4        #   calculate &numbers[i]
    la   $t2, numbers       #
    add  $t3, $t1, $t2      #
    lw   $a0, ($t3)         #   load numbers[i] into $a0
    
    blt  $a0, $t4, print_unordered
    
    move $t4, $a0
    
    addi $t0, $t0, 1
    j    check_loop        

ordered: 
    
    li   $a0, 0                 # printf("%d", 0)
    li   $v0, 1                 #
    syscall

    li   $a0, '\n'              # printf("%c", '\n');
    li   $v0, 11
    syscall

    jr   $ra    

print_unordered:

    li   $a0, 1                 # printf("%d", 1)
    li   $v0, 1                 #
    syscall

    li   $a0, '\n'              # printf("%c", '\n');
    li   $v0, 11
    syscall

    jr   $ra

.data

numbers:
    .word 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  # int numbers[10] = {0};
