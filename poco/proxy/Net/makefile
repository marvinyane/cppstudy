all:*.cpp
	gcc -c SocketAddressImpl.cpp IPAddressImpl.cpp IOManager.cpp -I/usr/local/include
	gcc -c main.cpp
	gcc *.o -L/usr/local/lib -lPocoNet -lPocoFoundation -o main

clean:
	rm *.o
	rm main
