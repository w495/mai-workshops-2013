CC=gcc
CC_FLAGS= -Wall -pedantic -std=c89 -Wall
NAME=fmax2sum
SRCDIR=./src
SRC=$(SRCDIR)/fmax2sum.c

.PHONY : all clean

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $< $(CC_FLAGS) -o $@

clean:
	rm  -f $(NAME)

