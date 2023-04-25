#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
        // define server socket
        int server_socket;
        server_socket = socket(AF_INET, SOCK_STREAM, 0);

        //define server address
        struct sockaddr_in server_address;
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = INADDR_ANY;
        server_address.sin_port = htons(64000);

        //bind socket
        bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));
        listen(server_socket, 5);
        printf("\nserver started listening\n");

        while(1){
                int client_socket;
                client_socket = accept(server_socket, NULL, NULL);
                char *msg = "Welcome, this is server Mohit";
                write(client_socket, msg, strlen(msg));
                printf("\nmessage sent...");
                char buff[256];

                read(client_socket, buff, sizeof(buff));
                printf("\nmessage received from client: %s\n", buff);
                char *p = strstr(buff, "END");
                if(p != NULL){
                        printf("\nserver is going to off\n");
                        break;
                }
        }
        close(server_socket);

}
