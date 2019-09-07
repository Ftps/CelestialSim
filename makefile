TARGET = exe
LIBS = -lm -lglut -lGLEW -lGL -lSDL2
CC = g++
CFLAGS = -Wall -pedantic -ggdb3 -o3

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
HEADERS = $(wildcard *.h)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@
	-rm -f *.o

clean:
	-rm -f $(TARGET)
	-rm -f *.o
