
OBJS	= findWords.o wordPuzzle.o
CC	= g++ -g -Wall -pedantic -std=c++11
DEPS	= wordPuzzle.h avlTree.h
DEPS1	= avlTree.h

all: findWords mainAVLtest


mainAVLtest.o: mainAVLtest.cpp $(DEPS1)
	$(CC) -Wall -c mainAVLtest.cpp

mainAVLtest: mainAVLtest.o mainAVLtest.o $(DEPS1)
	$(CC) -Wall -o mainAVLtest mainAVLtest.o


wordPuzzle.o: wordPuzzle.cpp $(DEPS)
	$(CC) -Wall -c wordPuzzle.cpp

findWords.o: findWords.cpp $(DEPS)
	$(CC) -Wall -c findWords.cpp

findWords: findWords.o wordPuzzle.o $(DEPS)
	$(CC) -Wall -o findWords $(OBJS)

# -----
# clean by removing object files.

clean:
	rm	mainAVLtest.o
	rm	$(OBJS)

