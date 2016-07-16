CC=gcc
CFLAGS=-I.

asmmake: jasm.c
	$(CC) -ggdb -o jasm jasm.c $(CFLAGS)