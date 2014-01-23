CC=gcc
CC_FLAGS= -Wall -pedantic -std=c89 -lm
NAME=wrong-table
SRCDIR=./src
SRC=$(SRCDIR)/$(NAME).c

.PHONY : all clean

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $< $(CC_FLAGS) -o $@

clean:
	rm  -f $(NAME)


