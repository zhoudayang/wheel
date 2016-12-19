all:singleton_test

singleton_test:singleton_test.o
	g++ -o singleton_test singleton_test.o

CXXFLAGS = -std=c++11 -O2 -g -Wall 
main.o:main.cc singleton.h

clean:
	-rm -rf *.o singleton_test
