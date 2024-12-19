# Level0 Walkthrough

## Analyzing the Program with GDB

1. **Disassemble the `main` function**:  
   Using the command `disas main`, we found that the program contains **two `main` functions**:
   - One of them causes a segmentation fault.
   - The other one seems to work correctly.

2. **Behavior of the Program**:  
   - The program uses `atoi(argv[1])` to convert the first command-line argument to an integer.
   - It compares the result of `atoi(argv[1])` to `423`:
     - **If the value is `423`**, the program takes the correct execution path and works properly.
     - **If the value is not `423`**, the program jumps to the other `main` function, which segfaults.

---

## Running the Program

1. **Execute the Program with the Correct Input**:  
   We ran the program with the following command:  
   ```bash
   ./level0 423
   ```
   This ensures the program follows the correct path (i.e., the non-segfaulting main).

2. **Accessing the Password**:
    After the program executed successfully, we used the command:
    ```bash
    cat /home/user/level1/.pass
    ```
    this displayed the password for the next level.
    
3. **Exit the Session**:
    run the ```exit``` command

## Moving to level1

1. **Swith User to level1**:
    Run ```su level1```

2. **Authenticate with the Password**:
    Use the password you find within the ./level0