#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_LINE_LENGTH 1024
#define MAX_CONN_QUEUE 1


int main(int argc, char const* argv[]) {
  char server_ip[16], client_ip[16];  
  uint server_port, client_port;
  int sock_fd, new_conn_sock_fd;
  struct sockaddr_in server_addr, client_addr;
  char buffer[MAX_LINE_LENGTH];
  int msglen;
  socklen_t client_addr_len;
  FILE *fptr;
  char fname[64];
  int bind_res, listen_res;

  /* Process input arguments */
  if (argc < 3) {
    printf("Usage: $tcp_server SERVER_IP SERVER_PORT\n");
    exit(1);
  }
  strcpy(server_ip, argv[1]);
  server_port = atoi(argv[2]);

  /* Create TCP socket */
  // Use the socket function to create a socket for TCP communication.
  // sock_fd = socket(...);  

  sock_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (sock_fd < 0) {
    printf("Error creatinging socket\n");
    exit(1);
  }

  /* Set socket information */
  // Set address family, IP address, and port number to server_addr
  // that will be used to identify the server address.
  // Hint: Check server_addr's structure
  // Hint: Host vs network byte order
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(server_ip);
  server_addr.sin_port = htons(server_port);    

  /* Bind socket */
  // Bind socket to server's address to setup server's address.
  // bind_res = bind(...);

  bind_res = bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

  if ( bind_res < 0) {
    printf("Error binding socket\n");
    exit(1);
  } else {
    printf("Bind socket to %s %d\n", server_ip, server_port);
  }

  /* Listen to new connection */
  // Start listening
  // listen_res = listen(...);

  listen_res = listen(sock_fd, MAX_CONN_QUEUE); // Listen to new connection

  if ( listen_res < 0) {
    printf("Error listen\n");
    exit(1);
  } else {
    printf("Lisening...\n");
  }

  /* Accept new connection */
  // Accept multiple connections one-by-one. Each connection write
  // to a file, VISTEC_TCP_CLIENT-IP_CLIENT-PORT.txt.
  printf("TCP Server start (%s, %d)\n", server_ip, server_port);
  client_addr_len = sizeof(client_addr);  

  while (1) {
    // Accept a new connection.
    // new_conn_sock_fd = accept(...);

    new_conn_sock_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &client_addr_len);

    if (new_conn_sock_fd < 0) {
      printf("Error accepting new connection\n");
      exit(1);
    }
    
    // Extract client's ip and port to client_ip and client_port
    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip)); // Convert IP address from network byte order to host byte order
    client_port = ntohs(client_addr.sin_port); // Convert port number from network byte order to host byte order

    printf("New connection from %s %d\n", client_ip, client_port); // %s and %d are format specifiers for string and integer, respectively.


    /* Open file to write */
    sprintf(fname, "VISTEC_TCP_%s_%d.txt", client_ip, client_port); 
    fptr = fopen(fname, "w");
    if (fptr == NULL) {
      printf("Error opening a file\n");
      exit(1);
    }      

    /* Start receiving TCP packets */
    // Receive messages from a client and write it to the output file.
    // while ( (msglen = recv(...)) > 0 ) {
    //   fwrite(buffer, msglen, 1, fptr);      
    // }
    while ( (msglen = recv(new_conn_sock_fd, buffer, MAX_LINE_LENGTH, 0)) > 0 ) {
      fwrite(buffer, msglen, 1, fptr);
      bzero(buffer, MAX_LINE_LENGTH);      
    }

    /* Close the new socket & file */
    // close(...);
    fclose(fptr);
  }

  /* Close socket */
  // close(...);
  close(sock_fd);

  return 0;
}
