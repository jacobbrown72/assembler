#include <stdio.h>
#include <stdlib.h>

#define ROM_SIZE 65536
#define RAM_SIZE 65536

/* Function header from print out ROM table to a file */
void print_rom(int* ROM, FILE* f, int size);

int main(int argc, char* argv[]){
	/* Variable declaration */
	FILE* fASM;
	FILE* fROM;
	int i;
	int ROM[ROM_SIZE];
	int size;
	int fp = 0;
	char* buffer;
	char line[100];
	
	/* Initialize ROM to 0 */
	for(i=0; i<ROM_SIZE; i++){
		ROM[i] = 0;
	}
	
	/* Open ROM file for writing */
	fROM = fopen("rom.mif", "w");
	
	if(argc < 2){
		/* No ASM file to assemble */
		printf("No asm file provided, generating empty ROM\n");
		print_rom(ROM, fROM, ROM_SIZE);
		printf("ROM generated\n");
	}
	else{
		/* Open asembly file for reading */
		fASM = fopen(argv[1], "r");
		
		/* Read ASM file into a buffer */
		fseek(fASM, 0, SEEK_END);
		size = ftell(fASM);
		rewind(fASM);
		buffer = malloc((size+1) * sizeof(char));
		fread(buffer, size, 1, fASM);
		buffer[size] = 0;
		
		/* Close ASM file */
		fclose(fASM);
		
		/* Process the file buffer */
		while(buffer[fp] != 0){
			/* Reset temporary pointer */
			i = 0;
			
			/* Read a line from the buffer */
			while(buffer[fp] != '\n'){
				if(buffer[fp]>32 && buffer[fp]<126){
					line[i++] = buffer[fp++];
				}
			}
			line[i] = 0;
			fp++;
			
			/* process line buffer */
			if(line[0] == '.'){
				/* Pre-assembler directive */
			}
			
		}
		
		/* Generate ROM file */
		
	}
	
	/* Close ROM file */
	fclose(fROM);
}

void print_rom(int* ROM, FILE* f, int size){
	int i;
	fprintf(f, "DEPTH = 65536;\n");
	fprintf(f, "WIDTH = 16;\n");
	fprintf(f, "ADDRESS_RADIX = HEX;\n");
	fprintf(f, "DATA_RADIX = HEX;\n");
	fprintf(f, "CONTENT\n");
	fprintf(f, "BEGIN\n");
	for(i=0; i<size; i++){
		fprintf(f, "%04x : %04x;\n", i, ROM[i]);
	}
	fprintf(f, "END;\n");
}