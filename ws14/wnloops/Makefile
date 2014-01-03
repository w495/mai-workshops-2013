CC=gcc
CC_FLAGS= -pedantic -std=c89 -ansi
SRCDIR=./src

all: wnloops-1 wnloops-2

wnloops-1:
	$(CC) $(SRCDIR)/wnloops-1.c $(CC_FLAGS) -o ./wnloops-1

wnloops-2:
	$(CC) $(SRCDIR)/wnloops-2.c $(CC_FLAGS) -o ./wnloops-2

# -----------------------------------------------------------------------	
clean:
	rm  -f wnloops-1 wnloops-2
