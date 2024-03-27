.text
.globl echo

echo:
    push %ebp
    movl %esp, %ebp

    # Something happens #

    movl %ebp, %esp
    pop %ebp