# read 10 numbers into an array
# swap any pairs of of number which are out of order
# then print the 10 numbers

# i in register $t0,
# registers $t1 - $t3 used to hold temporary results

main:

    li   $t0, 0         # i = 0
loop0:
    bge  $t0, 10, end0  # while (i < 10) {

    li   $v0, 5         #   scanf("%d", &numbers[i]);
    syscall             #

    mul  $t1, $t0, 4    #   calculate &numbers[i]
    la   $t2, numbers   #
    add  $t3, $t1, $t2  #
    sw   $v0, ($t3)     #   store entered number in array

    addi $t0, $t0, 1    #   i++;
    j    loop0          # }

end0:
    li   $t0, 1         # i = 1

loop1:
    bge  $t0, 10, end1  # while (i < 10) {

    mul  $t1, $t0, 4    #   calculate &numbers[i]
    la   $t2, numbers   #
    add  $t3, $t1, $t2  #
    lw   $t4, ($t3)     #   load numbers[i] into $t4
    
    sub  $t6, $t0, 1    #
    mul  $t1, $t6, 4    #   calculate &numbers[i-1]
    la   $t2, numbers   #
    add  $t7, $t1, $t2  #   
    lw   $t5, ($t7)     #   load numbers[i-1] into $t5
    
    blt  $t4, $t5, swap_numbers
    
    addi $t0, $t0, 1    #   i++
    j    loop1

swap_numbers:
    
    sw   $t4, ($t7)
    sw   $t5, ($t3)
    
    addi $t0, $t0, 1    #   i++
    j    loop1
    
end1: 
    li   $t0, 0         # i = 0

print_loop:    
    bge  $t0, 10, print_end  # while (i < 10) {

    mul  $t1, $t0, 4    #   calculate &numbers[i]
    la   $t2, numbers   #
    add  $t3, $t1, $t2  #
    lw   $a0, ($t3)     #   load numbers[i] into $t0    
    li   $v0, 1         #   printf("%d", numbers[i])
    syscall

    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall

    addi $t0, $t0, 1    #   i++
    j    print_loop          # }

print_end:
    li   $v0, 0
    jr   $ra            # return 0

.data

numbers:
    .word 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  # int numbers[10] = {0};
