# Read a number n and print the first n tetrahedral numbers
# https://en.wikipedia.org/wiki/Tetrahedral_number

main:                  # int main(void) {

    la   $a0, prompt   # printf("Enter how many: ");
    li   $v0, 4
    syscall

    li   $v0, 5         # scanf("%d", number);
    syscall
    
    move $t0, $v0
    li   $t1, 1
    li   $t2, 2
    li   $t3, 0
    li   $t4, 0
    
loop: 
    bgt  $t1, $t0, end
    
    mul  $t3, $t1, $t2
    srl  $t3, $t3, 1
    add $t4, $t4, $t3
    
    move   $a0, $t4
    li   $v0, 1
    syscall
    
    li   $a0, '\n'
    li   $v0, 11
    syscall
    
    addi $t1, $t1, 1   
    addi $t2, $t2, 1
    
    b    loop
    

end:
    jr   $ra           # return

    .data
prompt:
    .asciiz "Enter how many: "
