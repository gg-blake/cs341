.text
.globl echo

echo:
    push %ebp
    movl %esp, %ebp
    subl $8, %esp # Make space for local variables
    movb 12(%ebp), %bl # Store the character as a byte in bl register (least significant half of bits)
    movl 8(%ebp), %edx # Store the port number in edx register
    
    movl $0, %ecx # Use ebx register as a counter

    # Turn on DTR and RTS
    movb $0x2fc, %dl # Modem control
    inb (%dx), %al # Get current byte from port
    orb $0x03, %al # Set 2 least significant bits
    outb %al, (%dx) # Set control register

    # Get DSR Status
    movb $0xfe, %dl # Move modem status to dl register

loop1:
    # Wait for RTS, CTS, and DCD
    inb (%dx), %al # Get current modem control signal
    andb $0xb0, %al # Get RTS, CTS, and DCD signals, move them to al register
    xorb $0xb0, %al # Ensure all signals are true...
    jnz loop1 # ...Otherwise, keep checking in the loop

loop2:
    # Reading a byte from received data
    movb $0x2fd, %dl # Store address of line status in dx register
    inb (%dx), %al # Move line status to al register
    andb $0x01, %al # Check data ready
    jz loop2 # Keep looping until data ready
    movb $0xf8, %dl # Move i/o data address to dl register
    inb (%dx), %al # Read a byte from the port at i/o data address
    movb %al, %cl # Save read data to cl register
    cmpb %cl, %bl # If the read i/o char matches the echo char then end
    je stop
    movb $0x2fd, %dl # Store address of line status in dx register again

xmit:
    # Read THRE (The Holding Register Empty)
    inb (%dx), %al # Store THRE in al register
    andb $0x20, %al # Check THRE 
    jz loop2 # If not, try again
    movb %cl, %al # Restore the value
    movb $0xf8, %dl # Set up the mask
    outb %al, (%dx) # Write the port
    jmp loop2 # Try again

stop:
    movl %ebp, %esp # Restore stack pointer
    pop %ebp # Restore base pointer
    ret # Return to C
    .end