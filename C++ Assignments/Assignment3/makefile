CC=g++
CCFLAGS=-std=c++11
LIBS=-lm

huffencode: HuffmanTree.o HuffmanNode.o driver.o
		$(CC) $(CCFLAGS) HuffmanTree.o HuffmanNode.o driver.o -o huffencode $(LIBS)
		
HuffmanTree.o: HuffmanTree.cpp HuffmanTree.h
				$(CC) $(CCFLAGS) HuffmanTree.cpp -c

HuffmanNode.o: HuffmanNode.cpp HuffmanNode.h
				$(CC) $(CCFLAGS) HuffmanNode.cpp -c

				
driver.o: driver.cpp
		$(CC) $(CCFLAGS) driver.cpp -c

		
clean: 
		@rm -f *.o
		@rm -f huffencode
		

