CC            = gcc
CFLAGS        = -Wall -pedantic -ansi
SRC           = src/indicator.c
MAIN_SRC      = src/main.c
TARGET        = indicator

.SUFFIXES: .c

all: $(TARGET)

$(TARGET): $(SRC) $(MAIN_SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm $(TARGET)