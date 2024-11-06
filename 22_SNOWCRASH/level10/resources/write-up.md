# A binary designed to connect to a remote host on port 6969 and send a file to the host.
- When we first run the executable, we have: 
    ./level10

# The program checks if there are 3 arguments.

# If it does not have access to the first argument (the file), it returns a message and terminates.
# Therefore, we need to create access to the file named "token".

# The binary attempts to connect on port 6969.

# If it succeeds, it sends a message ".().\n" to the remote server.

# Then it opens the file (first argument), and once the file is read, it sends it to the remote server.
