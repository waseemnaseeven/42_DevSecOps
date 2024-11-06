# All at once 

```bash
gdb /bin/getflag

(gdb) b *main+72
Breakpoint 1 at 0x804898e
(gdb) b *main+452
Breakpoint 2 at 0x8048b0a
(gdb) run
Starting program: /bin/getflag 

Breakpoint 1, 0x0804898e in main ()
(gdb) print $eax
$1 = -1
(gdb) set $eax=0
(gdb) print $eax
$2 = 0
(gdb) cont
Continuing.

Breakpoint 2, 0x08048b0a in main ()
(gdb) print $eax
$3 = 2014
(gdb) set $eax=3014
(gdb) cont
Continuing.

```

# First research

```bash
find / -user level14 2>/dev/null
find / -user flag14 2>/dev/null
```

# We'll have to consider by pass the getflag itself

```bash
gdb /bin/getflag
```

# The reverse is protected

- So, we will have to `disas main` we find a `ptrace` call that blocked the reverse

- we can bypass `ptrace` that modifies the return value of ptrace cuz we can see they test it

```bash
   0x08048989 <+67>:    call   0x8048540 <ptrace@plt>
   0x0804898e <+72>:    test   %eax,%eax
```

- So change the value of eax to `0`

```bash
b *main+72
run
print $eax
set $eax=0
print $eax
cont
```

- We bypassed ptrace

# Changing UID

- Have to find the break point, of the UID comparison
- so `disas main` and `return` button till....

```bash
   0x08048afd <+439>:   call   0x80484b0 <getuid@plt>
   0x08048b02 <+444>:   mov    %eax,0x18(%esp)
   0x08048b06 <+448>:   mov    0x18(%esp),%eax
   0x08048b0a <+452>:   cmp    $0xbbe,%eax
```

- So : when we `id flag14` we have 3014, we'll have to change 2014 to 3014

```bash
Breakpoint 2, 0x08048b0a in main ()
(gdb) print $eax
$3 = 2014
(gdb) set $eax=3014
(gdb) cont
```

# Token, here do : su flag14
7QiHafiNa3HVozsaXkawuYrTstxbpABHD8CPnHJ

