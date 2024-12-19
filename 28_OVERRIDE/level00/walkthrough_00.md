# Level00 Walkthrough

## Analyzing the Program with GDB

1. **Whats happening**:  
    ```bash
    level00@OverRide:~$ ./level00 
    ***********************************
    *            -Level00 -           *
    ***********************************
    Password:



    ^C
    level00@OverRide:~$ ./level00 geq
    ***********************************
    *            -Level00 -           *
    ***********************************
    Password:password

    Invalid Password!
    level00@OverRide:~$ 
    ```

2. **Behavior of the Program**:  
    - Run `disas main`
    ```bash
    [...]
    0x080484de <+74>:    call   0x80483d0 <__isoc99_scanf@plt>
    0x080484e3 <+79>:    mov    0x1c(%esp),%eax   <---------> move the info from scanf into eax
    0x080484e7 <+83>:    cmp    $0x149c,%eax <---------> comparing eax to a value ???
    [...]
    ```

    just print it in decimal on gdb
    ```bash
    (gdb) print/d 0x149c
    $1 = 5276
    ```

---

## Running the Program

    ```bash
    level00@OverRide:~$ ./level00 
    ***********************************
    *            -Level00 -           *
    ***********************************
    Password:5276

    Authenticated!
    $ id 
    uid=1000(level00) gid=1000(level00) euid=1001(level01) egid=100(users) groups=1001(level01),100(users),1000(level00)
    $ whoami
    level01
    $ cat /home/users/level01/.pass
    uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
    ```

## Moving to level01

1. **Swith User to level01**:
    Run ```su level01```

2. **Authenticate with the Password**:
    Use the password you find within the ./level00