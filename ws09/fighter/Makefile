CC=gcc
CC_FLAGS= -pedantic -std=c90 -ansi
NAME=fighter
SRCDIR=./src
SRC=$(SRCDIR)/main.c
LIBDIR=$(SRCDIR)/lib
LIBMATH_SRC=$(LIBDIR)/libmath.c
LIBBIZ_SRC=$(LIBDIR)/libbiz.c

all: 
	$(CC) $(LIBMATH_SRC) $(LIBBIZ_SRC) $(SRC) $(CC_FLAGS) -o $(NAME)

# -----------------------------------------------------------------------	
clean:
	rm  -f $(NAME)

