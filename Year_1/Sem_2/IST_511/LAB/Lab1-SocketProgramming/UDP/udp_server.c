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
  struct sockaddr_in server_addr, client_addr;
  char buffer[MAX_LINE_LENGTH] = {0}; // Initialize buffer with 0
  int msglen; 
  socklen_t client_addr_len;
  int bind_res;
  FILE *fptr;

  /* Process input arguments */
  if (argc < 3) {
    printf("Usage: $udp_server SERVER_IP SERVER_PORT\n");
    exit(1);
  }
  strcpy(server_ip, argv[1]);
  server_port = atoi(argv[2]);

  /* Create UDP socket */
  // Use the socket function to create a socket for UDP communication.
  // sock_fd = socket(...); 

  // Create a socket for UDP communication
  sock_fd = socket(AF_INET, SOCK_DGRAM, IP_PROTOCOL);

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
  server_addr.sin_port = htons(server_port); // Convert to network byte order
  server_addr.sin_addr.s_addr = inet_addr(server_ip);
  
  /* Bind socket */
  // Bind socket to server's address to setup server's address.
  bind_res = bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

  if (bind_res < 0) {
    printf("Error binding socket\n");
    exit(1);
  } else {
    printf("Server is running at %s:%d\n", server_ip, server_port);
  }

  /* Open VISTEC_UDP.txt */
  fptr = fopen("VISTEC_UDP.txt", "w");

  if (fptr == NULL) {
    printf("Error opening a file\n");
    exit(1);
  }  

  /* Start receiving UDP data */
  // Receive messages from a client and write it to the output file.
  // Hint: You will need to design your protocol to break this loop
  //       when the client has nothing (in ASCii) more to send.

  printf("Receiving file from client...\n");
  while(1) {
    // msglen = recvfrom(...);
    client_addr_len = sizeof(client_addr);  
    msglen = recvfrom(sock_fd, buffer, MAX_LINE_LENGTH, 0, (struct sockaddr *)&client_addr, &client_addr_len);
    
    if (msglen < 0) {
      printf("Error receiving message\n");
      exit(1);
    }

    // Condition to break this loop
    if (strcmp(buffer, "END") == 0)
    {
      break;
    }
    
    //fwrite(buffer, msglen, 1, fptr);
    //fprintf(fptr, "%s", buffer);
    fwrite(buffer, 1, msglen, fptr);
    bzero(buffer, MAX_LINE_LENGTH); // Clear buffer
  }  
  
  printf("Done receiving file\n");

  /* Close socket & file */
  // close(...);
  fclose(fptr);
  close(sock_fd);

  printf("Close server\n");

  return 0;
}
