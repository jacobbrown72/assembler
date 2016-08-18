asmmake: jasm.c
	gcc jasm.c -ggdb -lm -I. -o jasm 
	
clean:
	rm jasm
