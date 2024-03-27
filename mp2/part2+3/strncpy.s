.text
.globl mystrncpy


# Returns:
#   Pointer to the destination string
mystrncpy:
    push %edi
    push %esi
    push %edx

    # Initialize the counter to zero
    xor %ecx, %ecx

copy_while:
    cmp %ecx, %edx
    je copy_while
    movb (%esi, %ecx), %al

    # Store the character in the destination string
    movb %al, (%edi, %ecx)
    inc %ecx
    test %al, %al
    jz copy_finish

    # Continue copying
    jmp copy_while

copy_finish:
    pop %edx
    pop %esi
    pop %edi

    # Null-terminate the destination string
    movb $0, (%edi, %ecx)

    ret
