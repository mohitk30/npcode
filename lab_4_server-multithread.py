import socket
import threading

def handle_client(conn,addr):
    print(f"Connected to {addr}")
    conn.send(b"Welcome to server !")
    
    while True:
        data=conn.recv(1024)
        if not data:
            print(f"Disconnected from {addr}")
            break
        print('Client sent data: ',data)
        conn.send(data)
        
def main():
    host='127.0.0.1'
    port=8000
    
    server_socket=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    server_socket.bind((host,port))
    server_socket.listen()
    print(f"Server listening on {host}:{port}")
    while True:
        conn,addr=server_socket.accept()
        client_thread=threading.Thread(target=handle_client,args=(conn,addr))
        client_thread.start()
        
if __name__=='__main__':
    main()