## LAB 1 Socket Programming

```
Directory Name: Lab1-SocketProgramming
|-UDP
|  |-udp_client.c
|  |-udp_server.c
|
|-TCP
|  |-tcp_client.c
|  |-tcp_server.c
|
|-README.md
|-Makefile
|-CMakeLists.txt
```

### To run the code, follow the steps below:

### Using CMake

<b>Build and compile the code</b>

```bash
mkdir build && cd build && cp ../VISTEC.txt . && cmake ..
```

And then run the following command to build the code if you want to build.

```bash
make [all | tcp_client | tcp_server | udp_client | udp_server]
```

<b>How to run the code</b><br>
For TCP

- Server

```bash
./tcp_server [Your IP Address] [Port Number]
[ex.] ./tcp_server 127.0.0.1 20204
```

- Client

```bash
./tcp_client [Your server IP] [Server Port Number]
[ex.] ./tcp_client 127.0.0.1 20204
```

For UDP

- Server

```bash
./udp_server [Your IP Address] [Port Number]
[ex.] ./udp_server 127.0.0.1 20204
```

- Client

```bash
./udp_client [Your server IP] [Server Port Number]
[ex.] ./udp_client 127.0.0.1 20204
```

### Using Makefile

<b>Build and compile the code</b><br>
table of target

| Target | Description        |
| ------ | ------------------ |
| all    | Build all the code |
| tc     | Build TCP client   |
| ts     | Build TCP server   |
| uc     | Build UDP client   |
| us     | Build UDP server   |

```bash
make [all | tc | ts | uc | us]
```

Clean the build

```bash
make clean
```

<b>How to run the code</b><br>
For TCP

- Server

```bash
./ts [Your server IP] [Server Port Number]
[ex.] ./ts 127.0.0.1 12345
```

- Client

```bash
./tc [Your IP Address] [Port Number]
[ex.] ./tc 127.0.0.1 12345
```

For UDP

- Server

```bash
./us [Your server IP] [Server Port Number]
[ex.] ./us 127.0.0.1 12345
```

- Client

```bash
./uc [Your IP Address] [Port Number]
[ex.] ./uc 127.0.0.1 12345
```
