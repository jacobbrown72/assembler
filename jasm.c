#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jasm.h"

int main(int argc, char* argv[]){
	/* Variable declaration */
	FILE* fASM;
	FILE* fROM;
	int ROM[ROM_SIZE];
	int size;
	int bufferptr = 0;
	int lineptr = 0;
	int temp = 0;
	char* buffer;
	char line[100];
	Instruction inst;
	char opcode[10];
	char rr[10];
	char rd[10];
	
	/* Initialize ROM to 0 */
	for(temp=0; temp<ROM_SIZE; temp++){
		ROM[temp] = 0;
	}
	
	/* Initialize instruction fields to -1 */
	inst.opcode = -1;
	inst.function = -1;
	inst.condition = -1;
	inst.rr = -1;
	inst.rd = -1;
	inst.immediate = -1;
	inst.ioaddr = -1;
	inst.diraddr = -1;
	
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
		while(buffer[bufferptr] != 0){
			/* Read instruction from file buffer */
			lineptr = 0;
			while(buffer[bufferptr] != '\n'){
			  line[lineptr] = buffer[bufferptr];
			  lineptr++;
			  bufferptr++;
			}
			line[lineptr] = 0;
			bufferptr++;
			
			/* Parse opcode */
			lineptr = 0;
			temp = 0;
			while(line[lineptr] != ' '){
			  opcode[temp] = line[lineptr];
			  temp++;
			  lineptr++;
			}
			opcode[temp] = 0;
			lineptr++;
			decodeinst(opcode, &inst);
			
			/* Parse operands */
			
			/* assemble instruction */
			
			/* Reset instruction struct */
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
	fprintf(fh, "    x\"%04x\"\n", rom[i]);
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

void decodeinst(char* opcode, Instruction* inst){
  /* default values */
  int op_code = -1;
  int function = -1;
  int cc = -1;
  
  if(strcmp(opcode, "nop")==0){
    op_code = NOP;
    function = 0;
  }
  if(strcmp(opcode, "hlta")==0){
    op_code = HLT;
    function = 1;
    cc = 0;
  }
  if(strcmp(opcode, "hlteq")==0){
    op_code = HLT;
    function = 1;
    cc = 1;
  }
  if(strcmp(opcode, "hltne")==0){
    op_code = HLT;
    function = 1;
    cc = 2;
  }
  if(strcmp(opcode, "hltvs")==0){
    op_code = HLT;
    function = 1;
    cc = 3;
  }
  if(strcmp(opcode, "hltvc")==0){
    op_code = HLT;
    function = 1;
    cc = 4;
  }
  if(strcmp(opcode, "hltmi")==0){
    op_code = HLT;
    function = 1;
    cc = 5;
  }
  if(strcmp(opcode, "hltpl")==0){
    op_code = HLT;
    function = 1;
    cc = 6;
  }
  if(strcmp(opcode, "hltcs")==0){
    op_code = HLT;
    function = 1;
    cc = 7;
  }
  if(strcmp(opcode, "hltcc")==0){
    op_code = HLT;
    function = 1;
    cc = 8;
  }
  if(strcmp(opcode, "hltlt")==0){
    op_code = HLT;
    function = 1;
    cc = 9;
  }
  if(strcmp(opcode, "hltge")==0){
    op_code = HLT;
    function = 1;
    cc = 10;
  }
  if(strcmp(opcode, "hltsh")==0){
    op_code = HLT;
    function = 1;
    cc = 11;
  }
  if(strcmp(opcode, "hltlo")==0){
    op_code = HLT;
    function = 1;
    cc = 12;
  }
  if(strcmp(opcode, "add")==0){
    op_code = ADD;
    function = 0;
  }
  if(strcmp(opcode, "adc")==0){
    op_code = ADC;
    function = 1;
  }
}










