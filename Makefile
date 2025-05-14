CC := gcc
FLAGS := -Wall
EXE := server

all: server.o
	$(CC) server.o -o $(EXE)

server.o: main.c
	$(CC) $(FLAGS) -c main.c -o $(EXE).o 

clean:
	rm *.o server
