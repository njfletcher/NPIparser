parser.exe: main.o
	g++ -O3 -lstdc++ -o parser.exe main.o
main.o: main.cpp
	g++ -O3 -c main.cpp
clean:
	rm parser.exe; rm -f *.o
