# read a number n and print the integers 1..n one per line

main:                 # int main(void)
    la   $a0, prompt  # printf("Enter a number: ");
    li   $v0, 4
    syscall

    li   $v0, 5       # scanf("%d", number);
    syscall

    
    li   $t0, 1
    move $t1, $v0

loop:
    bgt  $t0, $t1, end
    
    move $a0, $t0     # printf("%d", i);
    li   $v0, 1
    syscall
    
    
    li   $a0, '\n'    # printf("%c", '\n');
    li   $v0, 11
    syscall
    
    addi $t0, $t0, 1  # i++;
    
    b    loop         # goto loop;

end:
    jr   $ra          # return


    .data
prompt:
    .asciiz "Enter a number: "
    
    
