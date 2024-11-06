# Binary file level07, which uses the system function.

- Analyze with gdb or use ghidra  

- The program retrieves the value from the LOGNAME environment variable and then executes the echo command.

- We will modify the value of LOGNAME so that the program executes getflag.

export LOGNAME=";getflag;"

# Then run the level07 binary
./level07

# Explanation:

- ';' is a command separator that allows multiple commands to be executed sequentially on the same command line.
- After the first command is executed, the shell moves to the next one.

- When inserting ';' in the command string, the shell interprets it as two separate commands,
- first executing /bin/echo and then "getflag".

- By inserting ';' into the LOGNAME environment variable, we can add an additional command to the original command,
- allowing us to execute getflag after executing echo.

# Token obtained:
fiumuikeil55xe9cu4dood66h
