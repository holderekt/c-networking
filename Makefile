EXE = test

TCP_C_EXE = tcpclient
TCP_S_EXE = tcpserver

UDP_C_EXE = udpclient
UDP_S_EXE = udpserver

BUILD_DIR = ./
SRC_DIR = src
IDIR = include

SRC = ./src/util.c ./src/sockapi.c

TCP_C_SRC = ./src/tcp-client.c
TCP_S_SRC = ./src/tcp-server.c

UDP_C_SRC = ./src/udp-client.c
UDP_S_SRC = ./src/udp-server.c

CPPFLAGS += -I$(IDIR)

.PHONY: all clean

all: tcp udp

tcp: 
	$(CC) $(CPPFLAGS) -o $(TCP_C_EXE) $(TCP_C_SRC) $(SRC)
	$(CC) $(CPPFLAGS) -o $(TCP_S_EXE) $(TCP_S_SRC) $(SRC)

udp: 
	$(CC) $(CPPFLAGS) -o $(UDP_C_EXE) $(UDP_C_SRC) $(SRC)
	$(CC) $(CPPFLAGS) -o $(UDP_S_EXE) $(UDP_S_SRC) $(SRC)

clean:
	rm ./out/*