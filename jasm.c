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
	int opcode = -1;
	int function = -1;
	char* buffer;
	char line[100];
	char inst[10];
	char op1[10];
	char op2[10];
	
	/* Initialize ROM to 0 */
	for(temp=0; temp<ROM_SIZE; temp++){
		ROM[temp] = 0;
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
			  inst[temp] = line[lineptr];
			  temp++;
			  lineptr++;
			}
			inst[temp] = 0;
			lineptr++;
			opcode = decodeinst(inst);
			function = decodefunc(inst);
			
			/* Parse operands */
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

int decodeinst(char* inst){
  int opcode = NAI;
  if(strcmp(inst, "nop")==0)  opcode = NOP;
  if(strcmp(inst, "hlt")==0)  opcode = HLT;
  if(strcmp(inst, "add")==0)  opcode = ADD;
  if(strcmp(inst, "adc")==0)  opcode = ADC;
  if(strcmp(inst, "sub")==0)  opcode = SUB;
  if(strcmp(inst, "sbc")==0)  opcode = SBC;
  if(strcmp(inst, "adi")==0)  opcode = ADI;
  if(strcmp(inst, "adci")==0) opcode = ADCI;
  if(strcmp(inst, "sbi")==0)  opcode = SBI;
  if(strcmp(inst, "sbci")==0) opcode = SBCI;
  if(strcmp(inst, "and")==0)  opcode = AND;
  if(strcmp(inst, "or")==0)   opcode = OR;
  if(strcmp(inst, "ori")==0)  opcode = ORI;
  if(strcmp(inst, "eor")==0)  opcode = EOR;
  if(strcmp(inst, "eori")==0) opcode = EORI;
  if(strcmp(inst, "com")==0)  opcode = COM;
  if(strcmp(inst, "neg")==0)  opcdoe = NEG;
  if(strcmp(inst, "lsl")==0)  opcode = LSL;
  if(strcmp(inst, "rol")==0)  opcode = ROL;
  if(strcmp(inst, "lsr")==0)  opcode = LSR;
  if(strcmp(inst, "ror")==0)  opcode = ROR;
  if(strcmp(inst, "in")==0)   opcode = IN;
  if(strcmp(inst, "out")==0)  opcode = OUT;
  return opcode;
}

int decodefunc(char* inst){
  int function = -1;
  
  return function;
}










