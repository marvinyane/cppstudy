buffer.o : buffer.cpp
	g++ -g -c buffer.cpp -o buffer.o

main.o : main.cpp
	g++ -g -c main.cpp -fno-exceptions -o main.o

all:main.o buffer.o
	g++ main.o buffer.o -L/usr/local/lib -lPocoFoundation -o main

clean:
	rm main
	rm *.o
