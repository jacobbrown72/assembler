#include <stdio.h>
#include <stdlib.h>

#define ROM_SIZE 65536

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
	fROM = fopen("rom.vhd", "w");
	
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

void print_rom(int* rom, FILE* fh, int size){
  int i;
	fprintf(fh, "library ieee;\nuse ieee.std_logic_1164.all;\nuse ieee.numeric_std.all;\n\n");
	fprintf(fh, "entity rom is\n");
	fprintf(fh, "  port(\n");
	fprintf(fh, "    clk : in std_logic;\n");
	fprintf(fh, "    addra : in std_logic_vector(15 downto 0);\n");
	fprintf(fh, "    addrb : in std_logic_vector(15 downto 0);\n");
	fprintf(fh, "    qa : out std_logic_vector(15 downto 0);\n");
	fprintf(fh, "    qb : out std_logic_vector(15 downto 0)\n");
	fprintf(fh, "  );\n");
	fprintf(fh, "end rom;\n\n");
	fprintf(fh, "architecture rtl of rom is\n");
	fprintf(fh, "  type rom_mem is array(0 to 65535) of std_logic_vector(15 downto 0);\n");
	fprintf(fh, "  constant romtable  : rom_mem :=(\n");
	for(i=0;i<ROM_SIZE-1;i++){
	  fprintf(fh, "    x\"%04x\",\n", rom[i]);  
	}
	fprintf(fh, "    x\"%04x\"\n", i);
	fprintf(fh, "  );\n");
	fprintf(fh, "begin\n");
	fprintf(fh, "  process(clk)\n");
	fprintf(fh, "  begin\n");
	fprintf(fh, "    if(rising_edge(clk)) then\n");
	fprintf(fh, "      qa <= romtable(to_integer(unsigned(addra)));\n");
	fprintf(fh, "      qb <= romtable(to_integer(unsigned(addrb)));\n");
	fprintf(fh, "    end if;\n");
	fprintf(fh, "  end process;\n");
	fprintf(fh, "end rtl;\n");
}











