#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "jasm.h"

int main(int argc, char* argv[]){
	/* file pointers */
	FILE* fASM;
	FILE* fROM;
	/* rom array */
	int rom[ROM_SIZE];
	int size;
	int bufferptr = 0;
	int lineptr = 0;
	int temp = 0;
	char* buffer;
	char line[100];
	Instruction inst;
	char opcode[10];
	char opone[10];
	char optwo[10];
	int error;
	int linenmb;
	
	/* Initialize ROM to 0 */
	for(temp=0; temp<ROM_SIZE; temp++){
		rom[temp] = 0;
	}
	
	/* Open ROM file for writing */
	fROM = fopen("rom.vhd", "w");
	
	if(argc < 2){
		/* No ASM file to assemble */
		printf("No asm file provided, generating empty ROM\n");
		printrom(rom, fROM, ROM_SIZE);
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
		buffer[size+1] = 0;
		
		/* Close ASM file */
		fclose(fASM);
		
		/* initialize array pointers */
		bufferptr = 0;
		lineptr = 0;
		temp = 0;
		error = 0; 
		linenmb = 1;
		
		/* Process the file buffer */
		while(buffer[bufferptr] != 0){
			/* parse buffer until first non-whitespace character */
			while(buffer[bufferptr] < 33){
				bufferptr++;
			}
		  
			/* Read line from file buffer */
			lineptr = 0;
			while(buffer[bufferptr] != '\n'){
			  line[lineptr++] = buffer[bufferptr++];
			}
			bufferptr++;
			line[lineptr] = 0;
			
			/* Parse opcode */
			lineptr = 0;
			temp = 0;
			while(line[lineptr] != ' '){
			  opcode[temp++] = line[lineptr++];
			}
			lineptr++;
			opcode[temp] = 0;
			decodeinst(opcode, &inst);
			
			/* parse over whitespace */
			while(line[lineptr] < 33){
			  lineptr++;
			}
			
			/* Parse first operand */
			temp = 0;
			while(line[lineptr] != ','){
			  opone[temp++] = line[lineptr++];
			}
			lineptr++;
			opone[temp] = 0;
			decodeoperand(opone, &inst, 1);
			
			/* Parse over whitespace */
			while(line[lineptr] < 33){
			  lineptr++;
			}
			
			/* Parse second operand */
			temp = 0;
			while(line[lineptr] != 0){
			  optwo[temp++] = line[lineptr++];
			}
			optwo[temp] = 0;
			lineptr++;
			decodeoperand(optwo, &inst, 2);
			
			printf("Opcode   : %d\n", inst.opcode);
			printf("Operand 1: %d\n", inst.rd);
			printf("Operand 2: %d\n", inst.rr);
			
			/* assemble instruction */
			
			/* Reset instruction struct */
		}
		
		/* Generate ROM file */
		
	}
	
	/* Close ROM file */
	fclose(fROM);
}

void printrom(int* rom, FILE* fh, int size){
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

int findlabel(char* label){
  int i;
  int number = 0;
  for(i=0;i<LABELCNT;i++){
    if(strcmp(label, labels[i]) == 0){
      number = address[i];
    }
  }
  return number;
}

int convinteger(char* array, int length){
  int number = 0;
  int i = 0;
  int power = length - 1;
  int mult = pow(10, power);
  while(i<length){
    number = number + mult*(array[i++]-48);
    mult = mult / 10;
  }
  return number;
}

int convhex(char* array, int length){
  int number = 0;
  int value = 0;
  int i = 0;
  int power = length - 1;
  int mult = pow(16, power);
  while(i<length){
    if(array[i] == 'a' || array[i] == 'A'){
      value = 10;
    }
    else if(array[i] == 'b' || array[i] == 'B'){
      value = 11;
    }
    else if(array[i] == 'c' || array[i] == 'C'){
      value = 12;
    }
    else if(array[i] == 'd' || array[i] == 'D'){
      value = 13;
    }
    else if(array[i] == 'e' || array[i] == 'E'){
      value = 14;
    }
    else if(array[i] == 'f' || array[i] == 'F'){
      value = 15;
    }
    else{
      value = array[i]-48;
    }
    i++;
    number = number + mult*value;
    mult = mult / 16;
  }
}

void decodeoperand(char* operand, Instruction* inst, int op){
  int temp = 0;
  int i = 0;
  int registure = 0;
  int number = 0;
  char array[10];
  char label[20];
  if(operand[0] == 'r' && (operand[1] >= '0' && operand[1] <= '9')){
    /* Register */
    temp = 1;
    i = 0;
    while(operand[temp] != 0){
      array[i++] = operand[temp++];
    }
    array[i] = 0;
    registure = convinteger(array, i);
  }
  
  else if(operand[0] == '0' && operand[1] == 'x'){
    /* Hex immediate value */
    temp = 2;
    i = 0;
    while(operand[temp] != 0){
      array[i++] = operand[temp++];
    }
    array[i] = 0;
    number = convhex(array, i);
  }
  
  else if(operand[0] >= '0' && operand[0] <= '9'){
    /* decimal immediate value */
    temp = 0;
    while(operand[temp] != 0){
      array[i++] = operand[temp++];
    }
    array[i] = 0;
    number = convinteger(array, i);
  }
  
  else if(operand[0] >= 'A'){
    /* Label */
    temp = 0;
    i = 0;
    while(operand[temp] != 0){
      label[i++] = operand[temp++];
    }
    label[i] = 0;
    number = findlabel(label);
  }
  
}

int decodeinst(char* opcode, Instruction* inst){
  /* default values */
  int op_code = 0;
  int function = 0;
  int cc = 0;
  int error = OK;
  
  if(strcmp(opcode, "nop")==0){
    op_code = NOP;
    function = 0;
  }
  else if(strcmp(opcode, "hlta")==0){
    op_code = HLT;
    function = 1;
    cc = 0;
  }
  else if(strcmp(opcode, "hlteq")==0){
    op_code = HLT;
    function = 1;
    cc = 1;
  }
  else if(strcmp(opcode, "hltne")==0){
    op_code = HLT;
    function = 1;
    cc = 2;
  }
  else if(strcmp(opcode, "hltvs")==0){
    op_code = HLT;
    function = 1;
    cc = 3;
  }
  else if(strcmp(opcode, "hltvc")==0){
    op_code = HLT;
    function = 1;
    cc = 4;
  }
  else if(strcmp(opcode, "hltmi")==0){
    op_code = HLT;
    function = 1;
    cc = 5;
  }
  else if(strcmp(opcode, "hltpl")==0){
    op_code = HLT;
    function = 1;
    cc = 6;
  }
  else if(strcmp(opcode, "hltcs")==0){
    op_code = HLT;
    function = 1;
    cc = 7;
  }
  else if(strcmp(opcode, "hltcc")==0){
    op_code = HLT;
    function = 1;
    cc = 8;
  }
  else if(strcmp(opcode, "hltlt")==0){
    op_code = HLT;
    function = 1;
    cc = 9;
  }
  else if(strcmp(opcode, "hltge")==0){
    op_code = HLT;
    function = 1;
    cc = 10;
  }
  else if(strcmp(opcode, "hltsh")==0){
    op_code = HLT;
    function = 1;
    cc = 11;
  }
  else if(strcmp(opcode, "hltlo")==0){
    op_code = HLT;
    function = 1;
    cc = 12;
  }
  else if(strcmp(opcode, "add")==0){
    op_code = ADD;
    function = 0;
  }
  else if(strcmp(opcode, "adc")==0){
    op_code = ADC;
    function = 1;
  }
  else if(strcmp(opcode, "sub")==0){
    op_code = SUB;
    function = 0;
  }
  else if(strcmp(opcode, "sbc")==0){
    op_code = SBC;
    function = 1;
  }
  else if(strcmp(opcode, "adi")==0){
    op_code = ADI;
  }
  else if(strcmp(opcode, "adci")==0){
    op_code = ADCI;
  }
  else if(strcmp(opcode, "sbi")==0){
    op_code = SBI;
  }
  else if(strcmp(opcode, "sbci")==0){
    op_code = SBCI;
  }
  if(strcmp(opcode, "and")==0){
    op_code = AND;
    function = 0;
  }
  if(strcmp(opcode, "tst")==0){
    op_code = TST;
    function = 1;
  }
  if(strcmp(opcode, "andi")==0){
    op_code = ANDI;
  }
  if(strcmp(opcode, "or")==0){
    op_code = OR;
    function = 0;
  }
  if(strcmp(opcode, "ori")==0){
    op_code = ORI;
  }
  if(strcmp(opcode, "eor")==0){
    op_code = EOR;
    function = 0;
  }
  if(strcmp(opcode, "eori")==0){
    op_code = EORI;
  }
  if(strcmp(opcode, "com")==0){
    op_code = COM;
    function = 0;
  }
  if(strcmp(opcode, "neg")==0){
    op_code = NEG;
    function = 1;
  }
  if(strcmp(opcode, "lsl")==0){
    op_code = LSL;
    function = 0;
  }
  if(strcmp(opcode, "rol")==0){
    op_code = ROL;
    function = 1;
  }
  if(strcmp(opcode, "lsr")==0){
    op_code = LSR;
    function = 0;
  }
  if(strcmp(opcode, "ror")==0){
    op_code = ROR;
    function = 1;
  }
  if(strcmp(opcode, "in")==0){
    op_code = IN;
  }
  if(strcmp(opcode, "out")==0){
    op_code = OUT;
  }
  if(strcmp(opcode, "push")==0){
    op_code = PUSH;
    function = 0;
  }
  if(strcmp(opcode, "pop")==0){
    op_code = POP;
    function = 1;
  }
  if(strcmp(opcode, "mov")==0){
    op_code = MOV;
    function = 0;
  }
  if(strcmp(opcode, "mvw")==0){
    op_code = MVW;
    function = 1;
  }
  if(strcmp(opcode, "ldi")==0){
    op_code = LDI;
  }
  if(strcmp(opcode, "lds")==0){
    op_code = LDS;
    function = 0;
  }
  if(strcmp(opcode, "ld")==0){
    op_code = LD;
    function = 0;
  }
  if(strcmp(opcode, "lpm")==0){
    op_code = LPM;
    function = 1;
  }
  if(strcmp(opcode, "sts")==0){
    op_code = STS;
    function = 0;
  }
  if(strcmp(opcode, "st")==0){
    op_code = ST;
    function = 0;
  }
  if(strcmp(opcode, "cmp")==0){
    op_code = CMP;
    function = 0;
  }
  if(strcmp(opcode, "cpc")==0){
    op_code = CPC;
    function = 1;
  }
  if(strcmp(opcode, "cpi")==0){
    op_code = CPI;
  }
  if(strcmp(opcode, "bra")==0){
    op_code = BRA;
    function = 0;
    cc = 0;
  }
  if(strcmp(opcode, "breq")==0){
    op_code = BRA;
    function = 0;
    cc = 1;
  }
  if(strcmp(opcode, "brne")==0){
    op_code = BRA;
    function = 0;
    cc = 2;
  }
  if(strcmp(opcode, "brvs")==0){
    op_code = BRA;
    function = 0;
    cc = 3;
  }
  if(strcmp(opcode, "brvc")==0){
    op_code = BRA;
    function = 0;
    cc = 4;
  }
  if(strcmp(opcode, "brmi")==0){
    op_code = BRA;
    function = 0;
    cc = 5;
  }
  if(strcmp(opcode, "brpl")==0){
    op_code = BRA;
    function = 0;
    cc = 6;
  }
  if(strcmp(opcode, "brcs")==0){
    op_code = BRA;
    function = 0;
    cc = 7;
  }
  if(strcmp(opcode, "brcc")==0){
    op_code = BRA;
    function = 0;
    cc = 8;
  }
  if(strcmp(opcode, "brlt")==0){
    op_code = BRA;
    function = 0;
    cc = 9;
  }
  if(strcmp(opcode, "brge")==0){
    op_code = BRA;
    function = 0;
    cc = 10;
  }
  if(strcmp(opcode, "brsh")==0){
    op_code = BRA;
    function = 0;
    cc = 11;
  }
  if(strcmp(opcode, "brlo")==0){
    op_code = BRA;
    function = 0;
    cc = 12;
  }
  if(strcmp(opcode, "call")==0){
    op_code = CALL;
    function = 0;
  }
  if(strcmp(opcode, "ret")==0){
    op_code = RET;
    function = 0;
  }
  
  inst->opcode = op_code;
  inst->function = function;
  inst->condition = cc;
  
  return error;
}










