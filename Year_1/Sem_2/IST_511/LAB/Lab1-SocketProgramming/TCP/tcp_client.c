#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_LINE_LENGTH 1024
#define IP_PROTOCOL 0

int main(int argc, char const* argv[]) {
  char server_ip[16];
  uint server_port;
  int sock_fd;
  struct sockaddr_in server_addr;
  char buffer[MAX_LINE_LENGTH];
  int conn_status;
  FILE *fptr;

  // Step 1 - Process input arguments
  /* Process input arguments */
  if (argc < 3) {
    printf("Usage: $tcp_client SERVER_IP SERVER_PORT\n");
    exit(1);
  }
  strcpy(server_ip, argv[1]);
  server_port = atoi(argv[2]);

  /* Create TCP socket */
  // Use the socket function to create a socket for TCP communication.
  // sock_fd = socket(...);

  sock_fd = socket(AF_INET, SOCK_STREAM, IP_PROTOCOL);

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


  /* Connect to TCP server */
  // Connect to a server identified by server_addr
  // conn_stats = connect(...);

  conn_status = connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

  if ( conn_status < 0 ) {
    printf("Error connecting to TCP server\n");
    exit(1);
  } else {
    printf("Connected to TCP server\n");
  }

  /* Open VISTEC.txt */
  fptr = fopen("VISTEC.txt", "r");
  if (fptr == NULL) {
    printf("Error opening a file\n");
    exit(1);
  }

  /* Send messages through socket using send(...) command */

  printf("Sending file to server...\n");

  while (fgets(buffer, MAX_LINE_LENGTH, fptr) != NULL) {
    // send(...);
    if(send(sock_fd, buffer, strlen(buffer), 0) == -1){
      printf("Error sending message\n");
      exit(1);
    }
    bzero(buffer, MAX_LINE_LENGTH);
  }
  
  /* Close socket & file */
  // close(...);
  fclose(fptr);
  close(sock_fd);

  printf("Disconnected\n");

  return 0;
}
