# USER-MODE-LINUX-SYSTEM-CALL
• Add a system call using C language which could take one input, a string and print the count of characters of that string into the kernel log with Linux Kernel version 4.9.14
• Implemented a get pointer driver which could emits an 8-byte string which indicates a location of a memory to the user space
• Implemented a peek driver which could get an 8-byte memory location from the user space and read the value of this location in kernel space and emit the value to user space
• Implemented a poke driver which could get a 9-byte string from user space, the first 8-byte serves as the memory location in kernel space and write the last byte value to that location
