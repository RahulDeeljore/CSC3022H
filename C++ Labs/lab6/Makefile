all : tut

INCLUDE_DIRS =
CPPFLAGS = $(INCLUDE_DIRS) -std=c++11

LIB_DIRS = 
LIBS = 
LDFLAGS = $(LIBS) $(LIB_DIRS) -fPIC
OBJECTS = nineteen.o
PROGRAM = tut

$(PROGRAM) : $(OBJECTS)
	g++  $(OBJECTS) -o $(PROGRAM) $(LDFLAGS)

nineteen.o : nineteen.cpp
	g++ -c nineteen.cpp $(CPPFLAGS)
run :
	./$(PROGRAM)

clean :
	rm *.o
