all: main.exe

CFLAGS = -Wall -std=c++0x -o
CFLAGS_OBJ = -c $(CFLAGS)

main.exe: main.cpp Scene.o
	g++ $(CFLAGS) $@ $^

Scene.o: Scene.cpp
	g++ $(CFLAGS_OBJ) $@ $^
