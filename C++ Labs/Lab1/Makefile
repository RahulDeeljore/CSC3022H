CC=g++

        
driver: driver.o   
	$(CC) -o driver driver.o -std=c++11 -I ./factorial_library/ \
	-L ./factorial_library/ -lbrain_dead_factorial

driver.o: driver.cpp  
	$(CC) -c -o driver.o driver.cpp -std=c++11 -I ./factorial_library/ \
	-L ./factorial_library/ -lbrain_dead_factorial
run:
	export LD_LIBRARY_PATH=factorial_library/ && ./driver

clean:
	rm -f /*.o
