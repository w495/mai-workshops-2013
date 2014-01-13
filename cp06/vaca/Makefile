CC=gcc
CFLAGS=-lm -Wall -pedantic -std=c89
NAME=vaca
SRCDIR=./src
SRC=$(SRCDIR)/$(NAME).c

.PHONY : all clean

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm  -f $(NAME)

