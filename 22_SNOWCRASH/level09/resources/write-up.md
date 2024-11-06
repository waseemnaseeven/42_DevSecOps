# Try everything
- ./level09 token
- ./level09 hello
- ./level09 aaaaa

# We notice that each character is being added.
- We should transfer the token file into the host and use the reverse.py function
- scp -p 4242 ...

# Use the Python script to reverse the operation:
python3 /tmp/toto/reverse.py "$(cat token)"

# Result:
flag = f3iji1ju5yuevaus41q1afiuq

# Token obtained:
token = s5cAJpM8ev6XHw998pRWG728z
