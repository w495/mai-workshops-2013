CC=gcc
CC_FLAGS= -Wall -pedantic -std=c89
NAME=unishift
SRCDIR=./src
SRC=$(SRCDIR)/unishift.c

.PHONY : all clean

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $< $(CC_FLAGS) -o $@

clean:
	rm  -f $(NAME)
