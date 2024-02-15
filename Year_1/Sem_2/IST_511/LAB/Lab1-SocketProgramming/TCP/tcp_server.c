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
  int msglen, client_addr_len;
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
  if (sock_fd < 0) {
    printf("Error creatinging socket\n");
    exit(1);
  }

  /* Set socket information */
  // Set address family, IP address, and port number to server_addr
  // that will be used to identify the server address.
  // Hint: Check server_addr's structure
  // Hint: Host vs network byte order    

  
  /* Bind socket */
  // Bind socket to server's address to setup server's address.
  // bind_res = bind(...);
  if ( bind_res < 0) {
    printf("Error binding socket\n");
    exit(1);
  }

  /* Listen to new connection */
  // Start listening
  // listen_res = listen(...);
  if ( listen_res < 0) {
    printf("Error listen\n");
    exit(1);
  }

  /* Accept new connection */
  // Accept multiple connections one-by-one. Each connection write
  // to a file, VISTEC_TCP_CLIENT-IP_CLIENT-PORT.txt.
  printf("TCP Server start (%s, %d)\n", server_ip, server_port);
  client_addr_len = sizeof(client_addr);  
  while (1) {
    // Accept a new connection.
    // new_conn_sock_fd = accept(...);
    if (new_conn_sock_fd < 0) {
      printf("Error accepting new connection\n");
      exit(1);
    }
    // Extract client's ip and port to client_ip and client_port
    printf("New connection from %s %d\n", client_ip, client_port);


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

    /* Close the new socket & file */
    // close(...);
    fclose(fptr);
  }

  /* Close socket */
  // close(...);

  return 0;
}
