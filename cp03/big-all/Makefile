CC=gcc
CC_FLAGS= -Wall -pedantic -std=c89 -lm
NAME=big-solid
SRCDIR=./src
SRC=$(SRCDIR)/big-solid.c

.PHONY : all clean

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $< $(CC_FLAGS) -o $@

clean:
	rm  -f $(NAME)

