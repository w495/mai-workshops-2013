CC=gcc
CC_FLAGS= -pedantic -std=c89 -Wall
NAME=eouy
SRCDIR=./src
SRC=$(SRCDIR)/eouy.c

.PHONY : all clean

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $< $(CC_FLAGS) -o $@

clean:
	rm  -f $(NAME)
