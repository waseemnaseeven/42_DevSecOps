# Binary file 

- We have :
```bash
UID 2013 started us but we we expect 4242
```

- it has to be executed by specific UID which is 4242

- With `strings level13` we can find text zone
```bash
0123456
UID %d started us but we we expect %d
boe]!ai0FB@.:|L6l@A?>qJ}I
your token is %s
;*2$"$
GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3
```

- lets gdb, then `disas main`, then breakpoint getuid `b getuid`, then `run`, then `step` till getuid return
- we can see value : `print $eax`
- stock return value of getuid which is a `eax`

- change the value
```bash
set $eax=4242
```
- then `step`

# Token 
2A31L79asukciNyi8uppkEuSx
