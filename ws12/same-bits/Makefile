CC=gcc
CC_FLAGS= -pedantic -std=c89 -Wall
NAME=same-bits
SRCDIR=./src
SRC=$(SRCDIR)/same-bits.c

.PHONY : all clean

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $< $(CC_FLAGS) -o $@

clean:
	rm  -f $(NAME)

