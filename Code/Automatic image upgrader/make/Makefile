CC = g++
CFLAGS = -Wall -c -g 
OFLAGS = -o
BIN = ../bin/
SRC = ../src/
OBJ = ../obj/

all:$(BIN)main

$(OBJ)main.o:$(SRC)main.cpp
	$(CC) $(CFLAGS) $(SRC)main.cpp $(OFLAGS) $(OBJ)main.o

$(BIN)main:$(OBJ)main.o
	$(CC) $(OFLAGS) $(BIN)main $(OBJ)main.o

clean: 
	rm $(OBJ)*.o $(BIN)*

valgrind:$(BIN)main
	valgrind --leak-check=full $(BIN)main $(BIN) valgrind_report
