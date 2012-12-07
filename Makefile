all : poop
	

lang.o : lang.cpp lang.h
	g++ -g -c lang.cpp

continuation.o : continuation.cpp continuation.h
	g++ -g -c continuation.cpp

poop : lang.o continuation.o
	g++ -g continuation.o lang.o -o poop
