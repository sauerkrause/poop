all : poop


clean :
	rm *.o

poop.o : poop.cpp poop.h
	g++ -c poop.cpp

continuation.o : continuation.cpp continuation.h
	g++ -c continuation.cpp

poop : poop.o continuation.o
	g++ continuation.o poop.o -o poop
