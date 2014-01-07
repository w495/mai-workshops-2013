CC=g++
CC_FLAGS= -pedantic -std=c++98 -Wall
NAME=cppsort
SRCDIR=./src
SRC=$(SRCDIR)/$(NAME).cpp

.PHONY : all clean

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $< $(CC_FLAGS) -o $@

clean:
	rm  -f $(NAME)
