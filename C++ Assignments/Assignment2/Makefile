CC=g++
CCFLAGS=-std=c++11
LIBS=-lm

volimage: Volimage.o Driver.o
		$(CC) $(CCFLAGS) Volimage.o Driver.o -o volimage $(LIBS)
		
VolImage.o: Volimage.cpp Volimage.h
				$(CC) $(CCFLAGS) Volimage.cpp -c
				
Driver.o: Driver.cpp
		$(CC) $(CCFLAGS) Driver.cpp -c

		
clean: 
	@rm -f *.o
	@rm -f volimage
	@rm -f *.data
	@rm -f *.raw
