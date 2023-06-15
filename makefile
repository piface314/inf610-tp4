TARGET := inf610-tp4
CC := g++
CCFLAGS := -O2 -Wall -g -std=c++17
LDFLAGS := -Wall -lpthread -lm -ldl -lz -lncurses -rdynamic

.PHONY: all clean

all: obj bin bin/$(TARGET)

obj:
	mkdir -p obj

bin:
	mkdir -p bin

bin/$(TARGET): obj/main.o
	$(CC) -o bin/$(TARGET) obj/* $(LDFLAGS)

obj/main.o: src/main.cpp src/matrix.hpp
	$(CC) -c $(CCFLAGS) src/main.cpp -o obj/main.o

clean:
	rm -vfr obj bin
