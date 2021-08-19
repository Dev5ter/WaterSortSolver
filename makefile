CC = g++
CFLAGS = -std=c++11 -Wall -g
BIN = Solver

all: $(BIN)

Solver: main.cpp tube.cpp
	$(CC) $(CFLAGS) -o Solver main.cpp tube.cpp

clean:
	@rm -f $(BIN)