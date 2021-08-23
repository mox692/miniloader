.text
.global main

// 
// test binary loaded by miniloader
// 

main:
    pushq %rbp
    movq %rsp, %rbp

    nop
    nop
    nop

    pop %rbp
    ret
