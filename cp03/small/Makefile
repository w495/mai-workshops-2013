CC=gcc
CC_FLAGS= -Wall -pedantic -std=c89 -lm
NAME=small
SRCDIR=./src
SRC=$(SRCDIR)/small.c

.PHONY : all clean

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $< $(CC_FLAGS) -o $@

clean:
	rm  -f $(NAME)


