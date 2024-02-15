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
  FILE *fptr;

  /* Process input arguments */
  if (argc < 3) {
    printf("Usage: $udp_client SERVER_IP SERVER_PORT\n");
    exit(1);
  }
  strcpy(server_ip, argv[1]);
  server_port = atoi(argv[2]);

  /* Create UDP socket */
  // Use the socket function to create a socket for UDP communication.
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


  /* Open VISTEC.txt */
  fptr = fopen("VISTEC.txt", "r");
  if (fptr == NULL) {
    printf("Error opening a file\n");
    exit(1);
  }  

  
  /* Send messages through socket */
  // Open VISTEC.txt and send its content to the server using
  // sendto(...) command.
  // Hint: You will need to design your protocol to tell the server
  //       that the client has nothing (in ASCii) more to send.
  while (fgets(buffer, MAX_LINE_LENGTH, fptr) != NULL) {
    // sendto(...);
  }  


  /* Close socket & file */
  // close(...);
  fclose(fptr);

  return 0;
}
