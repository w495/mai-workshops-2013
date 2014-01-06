CC=gcc
CC_FLAGS= -pedantic -std=c89 -Wall
NAME=in-non-decreasing
SRCDIR=./src
SRC=$(SRCDIR)/in-non-decreasing.c

.PHONY : all clean

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $< $(CC_FLAGS) -o $@

clean:
	rm  -f $(NAME)

