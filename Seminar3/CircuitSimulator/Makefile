CPP=g++
CPPFLAGS=-std=c++17 -Wall -Wextra -Wpedantic -Weffc++ # -fmax-errors=1

all: Main.cc Circuit.o Component.o Connection.o
	$(CPP) $(CPPFLAGS) Main.cc Circuit.o Component.o Connection.o -g -o circ 

Circuit.o: Circuit.h Circuit.cc
	$(CPP) $(CPPFLAGS) -c Circuit.cc -o Circuit.o

Component.o: Component.h Component.cc
	$(CPP) $(CPPFLAGS) -c Component.cc -o Component.o

Connection.o: Connection.h Connection.cc
	$(CPP) $(CPPFLAGS) -c Connection.cc -o Connection.o

.PHONY: clean
clean:
	rm -f *.o

