# Level06 Walkthrough

## Analyzing the Program with GDB and ghidra
NEED TO GHIDRA 

1. **Whats happening**: 

```bash
level06@OverRide:~$ ./level06 
***********************************
*               level06           *
***********************************
-> Enter Login: level06  
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: password
```

- Nothing is happening after entering this informations, lets see what is it about with gdb and ghidra reverse. 
```bash
Starting program: /home/users/level06/level06
***********************************
*               level06           *
***********************************
-> Enter Login: bonjour
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 0
.---------------------------.
| !! TAMPERING DETECTED !!  |
'---------------------------'
[Inferior 1 (process 2162) exited with code 01]
```

- We noticed few conditions for login string : 
    - size > 5
    - no characters < 32 (ascii value)

- We noticed `main` and `auth` functions ask for login and a password, and then call the `auth` with this two variables as arguments and then check the return value of auth. If its `0` it print `Authenticated` and run `/bin/sh`. 

- We also noticed that there is a `ptrace` function (quick reminder from last level of snowcrash), we have to bypass it cuz we cant debug after, we'll have to set the return value to 0. Set a breakpoint way before ptrace, so 
```txt
0x080487b5 <+109>: call   0x80485f0 <ptrace@plt> <----> Before ptrace
0x08048866 <+286>:   cmp    -0x10(%ebp),%eax <-----> The serial value here 
0x080487ed <+165>:   mov    0x8(%ebp),%eax <-----> Jump here
```


- The serial number will be different for every username because it'll hash it thanks to its username. 

2. **Final walktrough**

```bash

(gdb) b *0x080487b5
Breakpoint 1 at 0x80487b5
(gdb) b *0x08048866
Breakpoint 2 at 0x8048866
(gdb) r
Starting program: /home/users/level06/level06 
[...]
-> Enter Login: waseem
[...]
-> Enter Serial: 0

Breakpoint 1, 0x080487b5 in auth ()
(gdb) jump *0x080487ed
Continuing at 0x80487ed.

Breakpoint 2, 0x08048866 in auth ()
(gdb) p *(int*)($ebp-0x10)
$1 = 6232797
(gdb) quit

[...]

level06@OverRide:~$ ./level06 
[...]
-> Enter Login: waseem
[...]
-> Enter Serial: 6232797
Authenticated!
$ whoami
level07
$ cat /home/users/level07/.pass
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
```

---


## Moving to level07

1. **Swith User to level07**:
    Run ```su level07```
    
```

2. **Authenticate with the Password**:
    
   
 