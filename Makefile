all: main.exe

CFLAGS = -Wall -std=c++0x -o
CFLAGS_OBJ = -c $(CFLAGS)

main.exe: main.cpp Particle.o Scene.o
	g++ $(CFLAGS) $@ $^

Particle.o: Particle.cpp
	g++ $(CFLAGS_OBJ) $@ $^

Scene.o: Scene.cpp
	g++ $(CFLAGS_OBJ) $@ $^
