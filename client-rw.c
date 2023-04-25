#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>

int main(int argc , char* argv[]){

    // define client socket
    int client_socket;
    client_socket=socket(AF_INET,SOCK_STREAM,0);
    
    
    // define client address
    struct sockaddr_in server_address;
    server_address.sin_family= AF_INET;
    server_address.sin_addr.s_addr= INADDR_ANY;
    server_address.sin_port= htons(60000);
    
    int connection_status=connect(client_socket,(struct sockaddr*)&server_address,sizeof(server_address));
    if( connection_status ==-1){
       printf("Error happen\n");
       exit(1);
     }
    
    
    char buff[256];
    
    read(client_socket,buff,sizeof(buff));
    printf("Message received: %s\n",buff);
    char *msg;
    msg=(char*)malloc(sizeof(char)*50);
    printf("Enter message for server:");
    fgets(msg,50,stdin);
    write(client_socket,msg,strlen(msg));
    close(client_socket);
    

  return 0;
}



