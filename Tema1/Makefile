CC = g++
CFLAGS = -Wall -g

all: build

build: TemaLFA

TemaLFA: Main.cpp
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

run: build
	./TemaLFA $(input) $(base)

clean:
	rm -f *.o *~ TemaLFA
