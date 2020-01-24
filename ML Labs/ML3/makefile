CPP=g++
CPPFLAGS=-std=c++11 -g
EXE_NAME=Find

$(EXE_NAME): Find.cpp
	$(CPP) -o $(EXE_NAME) Find.cpp $(CPPFLAGS)

clean:
	rm -f *.o $(EXE_NAME)

run:
	./Find
