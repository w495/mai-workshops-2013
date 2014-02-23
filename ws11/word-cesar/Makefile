CC=gcc
CC_FLAGS= -pedantic -std=c89 -Wall
NAME=word-cesar
SRCDIR=./src
SRC=$(SRCDIR)/$(NAME).c

.PHONY : all clean

all: $(NAME)

test:
	cat /dev/urandom  |  tr -dc [a-z] | fold -c256 | head  > x

$(NAME): $(SRC)
	$(CC) $< $(CC_FLAGS) -o $@

clean:
	rm  -f $(NAME)

