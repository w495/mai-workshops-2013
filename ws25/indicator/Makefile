CC            = gcc
CFLAGS        = -Wall -pedantic -ansi
SOURCE        = src/indicator.c
HEADER        = src/indicator.h
MAIN          = src/main.c
OBJECT        = indicator.o
TARGET        = indicator

.SUFFIXES: .c .o

all: $(TARGET)

$(TARGET): $(OBJECT) $(MAIN)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJECT): $(SOURCE) $(HEADER)
	$(CC) $(CFLAGS) $< -c -o $@

cleanall: clean
	rm -f $(TARGET)

clean:
	rm -f $(OBJECT)
	