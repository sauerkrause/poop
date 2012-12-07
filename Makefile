all : poop


clean :
	rm *.o

poop.o : poop.cpp poop.h
	g++ -g -c poop.cpp

continuation.o : continuation.cpp continuation.h
	g++ -g -c continuation.cpp

poop : poop.o continuation.o
	g++ -g continuation.o poop.o -o poop
