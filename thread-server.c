#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.d>
#include <pthread.h>

// the function for handling client in multithreading
void *todo_client(void *);

int main(){
    int socket_server, socket_client, sizeaddr;
    struct sockaddr_in server_addr, client_addr;

    //socket creation
    socket_server = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_server == -1){
        printf("Socket could not be created");
    }
    puts("Socket created");

    //fill the sockaddr_in structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8888);

    //bind the server socket
    if(bind(socket_server, (struct sockaddr *)&server_addr, sizeof(server_addr))< 0){
        // print the error meassage
        perror("Bind failed, Error");
        return 1;
    }
    puts("binding has been completed");

    //listen
    listen(socket_server, 3);

    //accept the incoming connection
    puts("waiting for incoming coinnection..");
    sizeaddr = sizeof(struct sockaddr_in);

    pthread_t thread_id;

    while((socket_client = accept(socket_server, (struct sockaddr*)&client_addr, (socklen_t*)&sizeaddr))){
        puts("Connection accepted");

        if(pthread_create(&thread_id, NULL, todo_client, (void*)&socket_client) < 0){
            perror("thread could not be created");