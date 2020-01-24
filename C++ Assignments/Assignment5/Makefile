CC=g++
CCFLAGS=-std=c++11
LIBS=-lm

samp: driver.o
		$(CC) $(CCFLAGS) driver.o -o samp $(LIBS)

				
driver.o: driver.cpp
		$(CC) $(CCFLAGS) driver.cpp -c


		
clean: 
		@rm -f *.o
		@rm -f samp
		
install: 
		@mv samp -/bin

