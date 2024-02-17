#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_LINE_LENGTH 1024
#define IP_PROTOCOL 0 // IP Protocol number; 0 means use default protocol

int main(int argc, char const* argv[]) {
  char server_ip[16];
  uint server_port;
  int sock_fd;
  struct sockaddr_in server_addr;
  char buffer[MAX_LINE_LENGTH] = {0}; // Initialize buffer with 0
  int msglen; 
  FILE *fptr;

  // Step 1 - Process input arguments
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
  
  // In network byte order is big endian | host byte order is little endian
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(server_ip); // Convert to network byte order
  server_addr.sin_port = htons(server_port); // Convert to network byte order 


  /* Open VISTEC.txt */
  fptr = fopen("VISTEC.txt", "r");

  if (fptr == NULL) {
    printf("Error opening a file\n");
    exit(1);
  }  

  
  /* Send messages through socket */
  // Open VISTEC.txt and send its content to the server using the socket.
  // Hint: You will need to design your protocol to tell the server
  //       that the client has nothing (in ASCii) more to send.
  printf("Sending file to server...\n");
  
  while (fgets(buffer, MAX_LINE_LENGTH, fptr) != NULL) {
    msglen = sendto(sock_fd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

    if (msglen < 0) {
      printf("Error sending message\n");
      exit(1);
    }
    bzero(buffer, MAX_LINE_LENGTH); // Clear buffer
  }  

  /* Close socket & file */
  // close(...);
  // Signal to end transmission
  strcpy(buffer, "END");
  sendto(sock_fd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
  printf("Done sending file\n");

  fclose(fptr);
  close(sock_fd);

  printf("Disconnected\n");

  return 0;
}
