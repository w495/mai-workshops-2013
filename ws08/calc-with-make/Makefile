## 
## Define a compiler.
## 
CC=gcc

## 
## Define compiler's flags
## 
CCFLAGS= -pedantic -std=c89 -Wall

## 
## The directory with the source code of the main program.
## 
SRCDIR=./src

## 
## The source directory of the `libcalc` library.
## 
LIBDIR=$(SRCDIR)/lib

## 
## The name of our library.
## 
LIB=libcalc

## 
## The source code of our library.
## 
LIBSRC=$(LIBDIR)/$(LIB).c

## 
## The header of our library.
## 
LIBINC=$(LIBDIR)/$(LIB).h

## 
## The object file of our library.
## 
LIBOBJ=./$(LIB).o

.SUFIXES: .h .c .o

##
## Targets that do not create the same name files.
##
.PHONY : all clean

all: argcalc linecalc stdcalc

##
## gcc libcalc.o src/argcalc.c -pedantic -std=c89 -Wall -o argcalc
##
argcalc: $(LIBOBJ) $(SRCDIR)/argcalc.c
	#
	#	Build calculator that uses command-line arguments.
	#
	$(CC) $^ $(CCFLAGS) -o $@

##
## gcc libcalc.o src/linecalc.c -pedantic -std=c89 -Wall -o linecalc
##
linecalc: $(LIBOBJ) $(SRCDIR)/linecalc.c 
	#
	#	Build the calculator that reads from the stdin-stream 
	#	until end of line.
	#
	$(CC) $^ $(CCFLAGS) -o $@

##
## gcc libcalc.o src/stdcalc.c -pedantic -std=c89 -Wall -o stdcalc
##
stdcalc: $(LIBOBJ) $(SRCDIR)/stdcalc.c 
	#
	#	Build the calculator that reads from the stdin-stream 
	#	until end of file.
	#
	$(CC) $^ $(CCFLAGS) -o $@

##
## Build library's object file 1 time 
## and then use it as many times as necessary.
## 
## gcc src/lib/libcalc.c -pedantic -std=c89 -Wall -c -o libcalc.o
##
$(LIBOBJ): $(LIBSRC) $(LIBINC)
	#
	#	Build libcalc library.
	#
	$(CC) $< $(CCFLAGS) -c -o $@

# -----------------------------------------------------------------------	
clean:
	rm  -f $(LIBOBJ) argcalc linecalc stdcalc

