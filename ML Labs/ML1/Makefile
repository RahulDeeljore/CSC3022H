CC=g++
LIBS=-lm


pca: PCA.o
	$(CC) PCA.o -o pca $(LIBS)


PCA.o: PCA.cpp
	$(CC) -c PCA.cpp





clean:
	@rm -f *.o
	@rm -f pca


run:
	./pca
