###PROGETTO DI RETI 1 DI LORENZO ROSSI, matr. 20031485 - MAKEFILE###
all: client server

client: client.o library.o
	gcc -g client.o library.o -o client

server: server.o library.o
	gcc -g server.o library.o -o server

client.o: client.c library.h
	gcc -g -c client.c

server.o: server.c library.h
	gcc -g -c server.c

library.o: library.c library.h
	gcc -g -c library.c

clean:
	rm *.o client server
