CC=gcc
CFLAGS=-lm -Wall -pedantic -std=c99
NAME=flt_epsilon
SRCDIR=./src
SRC=$(SRCDIR)/$(NAME).c

.PHONY : all clean

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm  -f $(NAME)

