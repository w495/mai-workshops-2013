CC=gcc
LD=ld

CC_FLAGS= -pedantic -std=c90 -ansi
CC_CPP_FLAGS= -E $(CC_FLAGS)
CC_ASM_FLAGS= -S $(CC_FLAGS)
CC_OBJ_FLAGS= -c $(CC_FLAGS)
CC_EXE_FLAGS= $(CC_FLAGS)

NAME=0-hello-world-0

SRC=$(NAME).c
CPP=$(NAME).prep.c
ASM=$(NAME).s
OBJ=$(NAME).o
EXE=$(NAME)

all: cpp asm obj exe

exe:
	$(CC) $(SRC) $(CC_EXE_FLAGS) -o $(EXE)

obj:
	$(CC) $(SRC) $(CC_OBJ_FLAGS) -o $(OBJ)

asm:
	$(CC) $(SRC) $(CC_ASM_FLAGS) -o $(ASM)

cpp:
	$(CC) $(SRC) $(CC_CPP_FLAGS) -o $(CPP)
	

clean:
	rm -f $(CPP) $(ASM) $(OBJ) $(EXE)

