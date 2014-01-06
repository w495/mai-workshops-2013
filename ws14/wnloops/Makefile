CC=gcc
CC_FLAGS= -pedantic -std=c89 -Wall
SRCDIR=./src

.PHONY : all clean

all: wnloops-1 wnloops-2

wnloops-1: $(SRCDIR)/wnloops-1.c 

wnloops-2: $(SRCDIR)/wnloops-1.c 

wnloops-%: $(SRCDIR)/wnloops-%.c 
	$(CC) $< $(CC_FLAGS) -o $@

clean:
	rm  -f wnloops-1 wnloops-2

