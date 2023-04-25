import socket
client_socket=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
host='127.0.0.1'
port=8000
client_socket.connect((host,port))

data=client_socket.recv(1024)
print(data.decode())

while True:
    message=input("Enter message: ")
    client_socket.send(message.encode())
    data=client_socket.recv(1024)
    print(f"Received from server: {data.decode()}")
    
client_socket.close()
