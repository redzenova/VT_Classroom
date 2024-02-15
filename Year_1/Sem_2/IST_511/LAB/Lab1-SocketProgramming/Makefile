CC=gcc
CFLAGS=-Wall

# Define the directories for TCP and UDP
TCP_DIR=TCP
UDP_DIR=UDP

# Define the targets for TCP and UDP clients and servers
TCP_SERVER=$(TCP_DIR)/tcp_server
TCP_CLIENT=$(TCP_DIR)/tcp_client
UDP_SERVER=$(UDP_DIR)/udp_server
UDP_CLIENT=$(UDP_DIR)/udp_client

# 'all' target will build both TCP and UDP clients and servers
all: $(TCP_SERVER) $(TCP_CLIENT) $(UDP_SERVER) $(UDP_CLIENT)

# Rules for building TCP server and client
$(TCP_SERVER): $(TCP_DIR)/tcp_server.c
	$(CC) $(CFLAGS) -o $(TCP_SERVER) $<

$(TCP_CLIENT): $(TCP_DIR)/tcp_client.c
	$(CC) $(CFLAGS) -o $(TCP_CLIENT) $<

# Rules for building UDP server and client
$(UDP_SERVER): $(UDP_DIR)/udp_server.c
	$(CC) $(CFLAGS) -o $(UDP_SERVER) $<

$(UDP_CLIENT): $(UDP_DIR)/udp_client.c
	$(CC) $(CFLAGS) -o $(UDP_CLIENT) $<

# 'clean' target to remove compiled binaries
clean:
	rm -f $(TCP_DIR)/tcp_client
	rm -f $(TCP_DIR)/tcp_server
	rm -f $(UDP_DIR)/udp_client
	rm -f $(UDP_DIR)/udp_server

.PHONY: all clean
