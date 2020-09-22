TARGET = libtrackear.so
LIBS = -lm
CC = gcc
CFLAGS = -g -Wall -fPIC

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall -shared $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
