TARGET = libtrackear.so
LIBS = -lm
CC = gcc
CFLAGS = -g -Wall -fPIC

.PHONY: default all clean

default: $(TARGET)
all: default

SOURCES = \
	$(wildcard *.c) \
	$(wildcard dto/*.c) \
	$(wildcard route/*.c) \
	$(wildcard dao/psql/*.c)

OBJECTS = $(SOURCES:.c=.o)
HEADERS = \
	$(wildcard *.h) \
	$(wildcard dto/*.h) \
	$(wildcard route/*.h) \
	$(wildcard dao/*.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall -shared $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
