CC=gcc
CC_FLAGS= -Wall -pedantic -std=c99
NAME=post-tree
SRCDIR=./src
SRC=$(SRCDIR)/$(NAME).c

.PHONY : all clean

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $< $(CC_FLAGS) -o $@

clean:
	rm  -rf *~
	rm  -f $(NAME)
