#compiler name
CC=g++
#flags that need to be passed to the compiler
CCFLAGS=-std=c++11
#the libraries that are referenced
LIBS=-lm

imageops: 	driver.o image.o	
		$(CC)	$(CCFLAGS) image.o driver.o -o imageops $(LIBS)
		
Image.o:	image.cpp 
		$(CC) $(CCFLAGS) image.cpp -c

driver.o:	driver.cpp
		$(CC) $(CCFLAGS) driver.cpp -c
		
clean:
		@rm -f *.o
		@rm -f imageops
