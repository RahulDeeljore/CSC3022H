CPP=g++
CPPFLAGS=-std=c++11 -g
EXE_NAME=test

$(EXE_NAME): test.cpp
	$(CPP) -o $(EXE_NAME) test.cpp $(CPPFLAGS)

clean:
	rm -f *.o $(EXE_NAME)

run:
	./test
