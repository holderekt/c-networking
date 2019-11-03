all: main
main: ../src/server.c ../include/sockapi.h ../include/util.h
	clear
	gcc -o server ../src/server.c ../src/sockapi.c ../src/util.c
	gcc -o client ../src/client.c ../src/sockapi.c ../src/util.c