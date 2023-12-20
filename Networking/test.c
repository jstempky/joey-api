#include <stdio.h>
#include <string.h>
/* #include <netinet/in.h> */
#include "Server.h"
#include <unistd.h>

void launch(
  struct Server *server
  ){
 char buffer[30000];
 printf("Server launched\n");
 while(1){
 
 int address_length = sizeof(server->address);
 int new_socket = accept(
   server->socket, 
   (struct sockaddr *)&server->address, 
   (socklen_t *)&address_length);
 read(new_socket, buffer, 30000);
 printf("%s\n", buffer);
 char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 14\n\nHello Joey API!";
 write(new_socket, hello, strlen(hello));
 close(new_socket);
 } 
}

int main(int argc, char *argv[])
{
 printf("1\n");
 struct Server server = server_constructor(
   AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8080, 10, launch
   );
 printf("2\n");
 server.launch(&server);
}
