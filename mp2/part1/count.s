.text
.globl count

count:
    pushl %ebp
    movl %esp, %ebp # Set the base pointer equal to %esp pointer
    movl 12(%ebp), %ecx # Move 32 bits from stack to ECX Register (Character)
    movl 8(%ebp), %edx # Move 32 bits from stack to EDX Register (String)
    movl $0, %eax # Set value of EAX register to 0 (To track character occurrence)

while:
    cmpb $0, (%edx) # Check if current character in string is the end
    je end # If so, break the loop, then return value in %eax
    cmpb %cl, (%edx) # Check if current character in string is equal to the searched character
    je increment # If so, make call to increment
    addl $1, %edx # Set the current character to the next character in the string
    jmp while # Jump to the beginning of the while loop from the beginning

increment:
    addl $1, %eax # Increment the number of occurrences by 1
    addl $1, %edx # Set the current character to the next character in the string
    jmp while # Restart the while loop from the beginning

end:
    leave # Leave the scope of the count.s
    ret # Return the value of %eax register
    