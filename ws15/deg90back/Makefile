CC=gcc
CC_FLAGS= -Wall -pedantic -std=c89
NAME=deg90back
SRCDIR=./src
SRC=$(SRCDIR)/deg90back.c

.PHONY : all clean

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $< $(CC_FLAGS) -o $@

clean:
	rm  -f $(NAME)

