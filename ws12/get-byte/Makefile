CC=gcc
CC_FLAGS= -pedantic -std=c89 -Wall
NAME=get-byte
SRCDIR=./src
SRC=$(SRCDIR)/${NAME}.c

.PHONY : all clean

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $< $(CC_FLAGS) -o $@

clean:
	rm  -f $(NAME)

