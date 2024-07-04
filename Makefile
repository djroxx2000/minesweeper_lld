CC = g++
CFLAGS = -I. -std=c++17
DEPS = Utility.hpp Grid.hpp

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

minesweeper: minesweeper.o Utility.o Grid.o
	$(CC) -o minesweeper minesweeper.o Utility.o Grid.o

.PHONY: clean

clean:
	del *.o *.exe

maclean:
	rm *.o minesweeper