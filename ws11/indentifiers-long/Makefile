CC=gcc
CC_FLAGS= -pedantic -std=c89 -Wall
NAME=indentifiers-long
SRCDIR=./src
SRC=$(SRCDIR)/indentifiers-long.c

.PHONY : all clean

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $< $(CC_FLAGS) -o $@

clean:
	rm  -f $(NAME)

