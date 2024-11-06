## View the passwd file
```bash
cat /etc/passwd
```
- /etc/passwd file stores essential information required during login. It stores user account info.
![passwd](image.png)

## Run a Debian 10 container interactively
```bash
docker run -it debian:10 /bin/bash
```

## Update the package list and install john the ripper
```bash
apt update && apt-get install john -y
```
- john the ripper is a hacking tools 

## Create a hash file named hash.txt
```bash
cat > hash.txt
here: password found in /etc/passwd
```

## Crack the hash with john
john hash.txt --show

## Result
abcdefg

```bash
su flag01
password: abcdefg
```

## Getting the flag
```bash
su level02
f2av5il02puano7naaf6adaaf
```

## Everytime you find the result 
- su flagXX
- getflag
- su levelXX