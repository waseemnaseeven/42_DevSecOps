# Level03 Walkthrough

- Vulnerability here is a about the `test` function and the success if calls to decrypt function.

- main():
    - seeds the random number generator used by the function rand
    - takes number from user input and save it into buff variable
    - call test function with 2 args, buff && 322424845

- test(int, int):

    - takes 2 int parameters
    - calculate the diff between these 2 numbers
    - if the diff strictly superior than 21 (>21) call decrypt function with random number, if less call decrypt with the diff value

- decrypt(int):

    - has a variable hash containing the following string Q}|u`sfg~sf{}|a

    La chaîne Q}|usfg~sf{}|a` est un texte chiffré qui sera décrypté dans le programme en utilisant une clé de décryptage via un XOR byte par byte
    
    - apply a XOR operation of each character with the argument sent (int)

    - compare the new hash content after the xor of its characters with the value `Congratulations`

    - we have limited tries of the solutions since the programm only deals with numbers and only call decrypt with logical value when the diff is less than or equal 21 :    
    
    Cela doit respecter cette logique la : 0≤diff≤21
 
    - la cle de decryptage correspond entre 1 et 21, donc entre 322424844 et 322424824

    - the solutions possible are the numbers between 322424824 and 322424844 THANKS to the test logic determined by the hash

    - if we try all of them numbers, we will get invalide password in all execpt the number that will make the diff equal to 18 which is 322424827

## Analyzing the Program with GDB

```bash
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Partial RELRO   Canary found      NX enabled    No PIE          No RPATH   No RUNPATH   /home/users/level03/level03
```

- We can see `Partial RELRO`, which means : 
```bash
RELRO (Relocation Read-Only)
RELRO est une protection qui rend certaines sections de la mémoire, notamment la Global Offset Table (GOT), en lecture seule après leur initialisation.
Cela empêche la modification des pointeurs dans la GOT par des attaques comme GOT overwrite.


Partial RELRO : Seule une partie des sections est protégée. La GOT reste modifiable, ce qui la rend vulnérable aux attaques.
Full RELRO : Toute la GOT est protégée en lecture seule après l'initialisation, empêchant les écrasements.
```

- We can see `canary found`, which means :
```bash
STACK CANARY
Un canary est une valeur spéciale insérée dans la pile avant les variables locales. Elle est vérifiée avant le retour de la fonction.
Si le canary est modifié,par exemple, à cause d'un buffer overflow, le programme détecte l'anomalie et termine l'exécution.

Canary found signifie que le binaire utilise des canaries pour protéger la pile contre les débordements.
```

- We can see `NX (Non-eXecutable)`, which means :
```bash
NX (Non-eXecutable)

La protection NX empêche l'exécution de code dans certaines régions de la mémoire, comme la stack ou la heap. Cela rend plus difficile l'exécution de shellcode injecté.
Si activé, les sections de la mémoire non marquées comme exécutable (par exemple, writable) ne peuvent pas être utilisées pour exécuter du code.

NX enabled indique que la pile est marquée comme non exécutable, empêchant l'exécution directe d'un shellcode injecté.
```

1. **Whats happening**:

```bash
level03@OverRide:~$ ./level03 
***********************************
*               level03         **
***********************************
Password:g

Invalid Password
```

- We are waiting for a password, lets `disas functions`
```bash
0x08048660  decrypt
0x08048747  test
0x0804885a  main
```

- `disas main`:
```bash
    0x0804885a <+0>:     push   %ebp
    0x0804885b <+1>:     mov    %esp,%ebp
    0x0804885d <+3>:     and    $0xfffffff0,%esp
    0x08048860 <+6>:     sub    $0x20,%esp <---- buffer size 32
```


```bash
   0x080488a4 <+74>:    mov    $0x8048a7b,%eax <--- "Password:"
   0x080488a9 <+79>:    mov    %eax,(%esp)
   0x080488ac <+82>:    call   0x8048480 <printf@plt>
   [...]
    0x080488c1 <+103>:   call   0x8048530 <__isoc99_scanf@plt> <--- take user input
    [...]
    0x080488c6 <+108>:   mov    0x1c(%esp),%eax
    0x080488ca <+112>:   movl   $0x1337d00d,0x4(%esp) <---- 322424845
    0x080488d2 <+120>:   mov    %eax,(%esp)
    0x080488d5 <+123>:   call   0x8048747 <test>
```


- `disas test`:
```bash
   0x08048747 <+0>:     push   %ebp
   0x08048748 <+1>:     mov    %esp,%ebp
   0x0804874a <+3>:     sub    $0x28,%esp <---- buffer size 40
```

```bash

   0x0804874d <+6>:     mov    0x8(%ebp),%eax
   0x08048750 <+9>:     mov    0xc(%ebp),%edx
   0x08048753 <+12>:    mov    %edx,%ecx <---- ecx = first paramter
   0x08048755 <+14>:    sub    %eax,%ecx <---- ecx = ecx (donc first param) - second param 
   0x08048757 <+16>:    mov    %ecx,%eax <---- eax = param1 - param2
   0x08048759 <+18>:    mov    %eax,-0xc(%ebp) 
   0x0804875c <+21>:    cmpl   $0x15,-0xc(%ebp) <---- si eax > 21 ---> decrypt(rand())  
   0x08048760 <+25>:    ja     0x804884a <test+259>

   [...] <--- repeating 15 times same instructions which is decrypt(eax = param1 - param2)
```

- `disas decrypt`:
```bash
[...]
    0x08048665 <+5>:     sub    $0x40,%esp <---- buffer size 64bytes
    0x08048668 <+8>:     mov    %gs:0x14,%eax <---- canary thing protection
[...]
    0x08048673 <+19>:    movl   $0x757c7d51,-0x1d(%ebp)
    => 0x0804867a <+26>:    movl   $0x67667360,-0x19(%ebp)
    0x08048681 <+33>:    movl   $0x7b66737e,-0x15(%ebp)
    0x08048688 <+40>:    movl   $0x33617c7d,-0x11(%ebp)
    hash="Q}|u`sfg~sf{}|a" <---- les quatres forment ce hash, merci ghidra
[...]
   0x080486f0 <+144>:   mov    %eax,%edx
   0x080486f2 <+146>:   mov    $0x80489c3,%eax <---- x/s 0x80489c3 = "Congratulations!"
[...]
   0x08048713 <+179>:   jne    0x8048723 <decrypt+195>
   0x08048715 <+181>:   movl   $0x80489d4,(%esp) <---- = "/bin/sh"
   0x0804871c <+188>:   call   0x80484e0 <system@plt>
   0x08048721 <+193>:   jmp    0x804872f <decrypt+207> 
```

---

## Running the Program 



```bash

level03@OverRide:~$ ./level03 
***********************************
*               level03         **
***********************************
Password:322424826

Invalid Password
level03@OverRide:~$ ./level03 
***********************************
*               level03         **
***********************************
Password:322424827
$ id
uid=1003(level03) gid=1003(level03) euid=1004(level04) egid=100(users) groups=1004(level04),100(users),1003(level03)
$ whoami
level04
$ cat /home/users/level04/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```

## Moving to level04

1. **Swith User to level04**:
    Run ```su level04```

2. **Authenticate with the Password**:
    
   
 