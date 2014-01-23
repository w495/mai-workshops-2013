CC=gcc
CC_FLAGS= -Wall -pedantic -std=c89 -lm
NAME=myfloat_t
SRCDIR=./src
SRC=$(SRCDIR)/$(NAME).c

.PHONY : all clean

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $< $(CC_FLAGS) -o $@

clean:
	rm  -f $(NAME)


