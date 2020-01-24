
CC=g++
CFLAGS=fPIC -shared -std=c++11

factorial.run: factorial.o 
	
	$(CC) -c -o factorial.o factorial.cpp -$(CFLAGS)

	$(CC) -o libbrain_dead_factorial.so factorial.o -$(CFLAGS)


clean:
	rm -f *.o
