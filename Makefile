# Makefile para compilaçao do LinearTransformusic
CC=g++
CFLAGS=-Wall -c
LDFLAGS=-Wall
SOURCES=main.cpp ./Graphics/view.cpp ./Music/music.cpp ./LinAlgebra/matrix.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=linearTransformusic
OBJECTSTOCLEAN=./Music/*.o ./Graphics/*.o ./LinAlgebra/*.o *.o

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTSTOCLEAN) $(EXECUTABLE)
