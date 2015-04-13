all:*.cpp
	g++ -c main.cpp -fno-exceptions
	g++ -c TimestampImpl.cpp EventImpl.cpp MutexImpl.cpp TimerImpl.cpp workThreadImpl.cpp task_runner.cpp -L/usr/local/lib -fexceptions
	g++ *.o -L/usr/local/lib -lPocoFoundation -lPocoUtil -o main

clean:
	rm *.o
	rm main
