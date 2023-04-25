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


int main(int argc , char* argv[]){

    // define server socket
    int server_socket;
    server_socket=socket(AF_INET,SOCK_STREAM,0);
    
    
    // define server address
    struct sockaddr_in server_address;
    server_address.sin_family= AF_INET;
    server_address.sin_addr.s_addr= INADDR_ANY;
    server_address.sin_port= htons(9010);
    
    // bin0
    bind(server_socket,(struct sockaddr*)&server_address,sizeof(server_address));
    listen(server_socket,5);
    printf("\n server started listening\n");
    
    
    while(1){
      
      int client_socket;
      client_socket=accept(server_socket,NULL,NULL);
      char* msg="Welcome to the server of Sanskar kumar";
      write(client_socket,msg,strlen(msg));
      printf("message sent ....\n");
      
      char buff[256];
      
      read(client_socket,buff,sizeof(buff));
      if(buff[0]=='1')
      {
        printf("You will get succcess\n");
      }
    //   printf(sizeof(buff));
      printf("Message received from client: %s\n",buff);
      char* p=strstr(buff,"END");
      if(p!=NULL){
           printf("Serevr is going to off\n");
           break;
      } 
      
    }
    
    

}

