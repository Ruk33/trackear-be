TARGET = trackear
LIBS = -lm -ldl -lpthread
CC = gcc
CFLAGS = -g -Wall

.PHONY: default all clean

default: $(TARGET)
all: default

SOURCES = $(wildcard *.c) $(wildcard data_structure/*.c) $(wildcard util/*.c)
OBJECTS = $(SOURCES:.c=.o)
HEADERS = $(wildcard *.h) $(wildcard data_structure/*.h) $(wildcard util/*.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
