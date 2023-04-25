import socket
HOST="127.0.0.1"
PORT=62000
BUFFER=1024

udp_client_socket=socket.socket(family=socket.AF_INET,type=socket.SOCK_DGRAM)
udp_client_socket.connect((HOST,PORT))
name=input('Enter your name : ')

udp_client_socket.send(bytes(name,'utf-8'))
print(udp_client_socket.recv(BUFFER).decode())


