import socket

HOST = "192.168.56.1" # its inet of 42, "ifconfig | grep inet"
PORT = 6969
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = (HOST, PORT)
server_socket.bind(server_address)
print(f"Server listening on {HOST}:{PORT}...")
server_socket.listen(5)

while True:
    client_socket, client_address = server_socket.accept()
    print(f"Connected by {client_address}")

    data = client_socket.recv(1024)
    if not data:
        break
    # print(f"Received: {data.decode('utf-8')}")
    print('received "%s"' % data)

    # response = "Hello from server!"
    # client_socket.send(response.encode('utf-8'))

    client_socket.close()