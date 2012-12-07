all : poop
	

poop.o : poop.cpp poop.h
	clang++ -g -c poop.cpp

continuation.o : continuation.cpp continuation.h
	clang++ -g -c continuation.cpp

poop : poop.o continuation.o
	clang++ -g continuation.o poop.o -o poop
