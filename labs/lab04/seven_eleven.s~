# Read a number and print positive multiples of 7 or 11 < n

main:                  # int main(void) {

    la   $a0, prompt   # printf("Enter a number: ");
    li   $v0, 4
    syscall

    li   $v0, 5         # scanf("%d", number);
    syscall

    move $t0, $v0
    li   $t1, 1

loop:    
    bge  $t1, $t0, end  # end condition      
    
    rem  $v0, $t1, 7     # divisible by 7, print
    beq  $v0, 0, print 
    
    rem  $v0, $t1, 11   # divisible by 11, print   
    beq  $v0, 0, print 
    
    addi $t1, $t1, 1
    
    b    loop
    
print:
    move $a0, $t1
    li   $v0, 1
    syscall
    
    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall
    
    addi $t1, $t1, 1
    
    b    loop
    
end:
    jr   $ra           # return


    .data
prompt:
    .asciiz "Enter a number: "
