import socket
HOST="127.0.0.1"
PORT=62000
BUFFER=1024
udp_server_socket=socket.socket(family=socket.AF_INET,type=socket.SOCK_DGRAM)
print('Congratulation !!, Socket is created')
udp_server_socket.bind((HOST,PORT))
print('Server Socket has been binded with host',HOST,'port',PORT)

while True:
    udp_client_msg,udp_client_address=udp_server_socket.recvfrom(BUFFER)
    print('Connected with client address',udp_client_address,'and message',udp_client_msg)
    udp_server_socket.sendto(bytes('Welcome to server,this is Vaibhav Yadav','utf-8'),udp_client_address)
    
    if udp_client_msg.decode()=='END':
        print('Server is going to exit')
        break