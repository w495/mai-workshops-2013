

CC=gcc

CC_FLAGS= -pedantic -std=c90 -ansi
SRCDIR=./src
#SRCDIR=$(PWD)/src
LIBDIR=$(SRCDIR)/lib
LIB=libcalc
LIB_SRC=$(LIBDIR)/$(LIB).c

all: argcalc linecalc stdcalc

argcalc:
	$(CC) $(LIB_SRC) $(SRCDIR)/argcalc.c $(CC_FLAGS) -o argcalc

linecalc:
	$(CC) $(LIB_SRC) $(SRCDIR)/linecalc.c $(CC_FLAGS) -o linecalc

stdcalc:
	$(CC) $(LIB_SRC) $(SRCDIR)/stdcalc.c $(CC_FLAGS) -o stdcalc

# -----------------------------------------------------------------------	
clean:
	rm  -f argcalc linecalc stdcalc

