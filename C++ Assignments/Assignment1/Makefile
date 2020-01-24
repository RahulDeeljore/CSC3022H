CC=g++

Driver: Driver.o Database.o StudentRecord.o
	$(CC) Driver.o Database.o StudentRecord.o -o Driver

main.o: Driver.cpp
	$(CC) -c Driver.cpp

database.o: Database.cpp Database.h
	$(CC) -c Database.cpp

StudentRecord.o: StudentRecord.cpp StudentRecord.h
	$(CC) -c StudentRecord.cpp

clean:
	rm *.o Driver

run:
	make
	./Driver
