CC=gcc
CC_FLAGS= -Wall -pedantic -std=c89 -Wall
NAME=curr-prev-letters
SRCDIR=./src
SRC=$(SRCDIR)/curr-prev-letters.c

.PHONY : all clean

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $< $(CC_FLAGS) -o $@

clean:
	rm  -f $(NAME)


