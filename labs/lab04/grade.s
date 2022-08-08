# read a mark and print the corresponding UNSW grade

main:
    la   $a0, prompt    # printf("Enter a mark: ");
    li   $v0, 4
    syscall

    li   $v0, 5         # scanf("%d", mark);
    syscall
    
    
    bge  $v0, 85, hidist
    bge  $v0, 75, dist
    bge  $v0, 65, credit
    bge  $v0, 50, pass  # pass condition
    
    
    la   $a0, fl        # printf("FL\n");
    li   $v0, 4
    syscall
    
    b    end

hidist:
    la   $a0, hd        # printf("HD\n");
    li   $v0, 4
    syscall
    b    end

dist:
    la   $a0, dn        # printf("DN\n");
    li   $v0, 4
    syscall
    b    end

credit:
    la   $a0, cr        # printf("CR\n");
    li   $v0, 4
    syscall
    b    end

pass:
    la   $a0, ps        # printf("PS\n");
    li   $v0, 4
    syscall
    b    end

end:
    jr   $ra            # return 

    .data
prompt:
    .asciiz "Enter a mark: "
fl:
    .asciiz "FL\n"
ps:
    .asciiz "PS\n"
cr:
    .asciiz "CR\n"
dn:
    .asciiz "DN\n"
hd:
    .asciiz "HD\n"
