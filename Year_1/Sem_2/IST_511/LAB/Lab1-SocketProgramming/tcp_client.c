#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_LINE_LENGTH 1024


int main(int argc, char const* argv[]) {
  char server_ip[16];
  uint server_port;
  int sock_fd;
  struct sockaddr_in server_addr;
  char buffer[MAX_LINE_LENGTH];
  int conn_status;
  FILE *fptr;

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
  if (sock_fd < 0) {
    printf("Error creatinging socket\n");
    exit(1);
  }

  /* Set socket information */
  // Set address family, IP address, and port number to server_addr
  // that will be used to identify the server address.
  // Hint: Check server_addr's structure
  // Hint: Host vs network byte order  


  /* Connect to TCP server */
  // Connect to a server identified by server_addr
  // conn_stats = connect(...);
  if ( conn_status < 0 ) {
    printf("Error connecting to TCP server\n");
    exit(1);
  }

  /* Open VISTEC.txt */
  fptr = fopen("VISTEC.txt", "r");
  if (fptr == NULL) {
    printf("Error opening a file\n");
    exit(1);
  }

  /* Send messages through socket using send(...) command */
  while (fgets(buffer, MAX_LINE_LENGTH, fptr) != NULL) {
    // send(...);
  }
  
  /* Close socket & file */
  // close(...);
  fclose(fptr);

  return 0;
}
