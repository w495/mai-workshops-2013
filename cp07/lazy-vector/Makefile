CC=gcc
CC_FLAGS= -Wall -pedantic -std=c99
NAME=lazy-vector
SRCDIR=./src
SRC=$(SRCDIR)/$(NAME).c

.PHONY : all clean

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $< $(CC_FLAGS) -o $@

clean:
	rm  *~
	rm  -f $(NAME1)
