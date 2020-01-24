CPP=g++
CPPFLAGS=-std=c++11 -g
EXE_NAME=K-means

$(EXE_NAME): K-means.cpp
	$(CPP) -o $(EXE_NAME) K-means.cpp $(CPPFLAGS)

clean:
	rm -f *.o $(EXE_NAME)

run:
	./K-means
