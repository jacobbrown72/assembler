#ifndef OPCODE_H
#define OPCODE_H

/* size of instruction memory */
#define ROM_SIZE 65536

/* Number of allowed labels */
#define LABELCNT 100

/* instruction struct definition */
typedef struct{
  int opcode;       // Instruction opcode
  int function;     // Function bit
  int condition;    // halt/branch condition code
  int rr;           // Source register
  int rd;           // Destination register
  int immediate;    // immediate operand
  int ioaddr;       // I/O address
  int diraddr;      // Direct address
} Instruction;

/* Function header to print out ROM table to a file */
void printrom(int* ROM, FILE* f, int size);

/* Function header to determine opcode */
void decodeinst(char* opcode, Instruction* inst);

/* Function header to parse operands */
void decodeoperand(char* operand, Instruction* inst, int op);

/* Function header to convert array to integer */
int convinteger(char* array, int length);
int convhex(char* array, int length);

/* Function to sear labels */
int findlable(char* label);

/* Label array */
<<<<<<< HEAD
char labels[LABELCNT][20];
=======
char* labels[LABELCNT];
>>>>>>> a2dd4bf754047560fe9841e7418e9fa3ff95203b
int address[LABELCNT];

/* Error codes */
#define OK 0

/* opcode definitions */
#define OPBIT 11
#define NAI -1
#define NOP 0
#define HLT 0
#define ADD 1
#define ADC 1
#define SUB 2
#define SBC 2
#define ADI 3
#define ADCI 4
#define SBI 5
#define SBCI 6
#define AND 7
#define TST 7
#define ANDI 8
#define OR 9
#define ORI 10
#define EOR 11
#define EORI 12
#define COM 13
#define NEG 13
#define LSL 14
#define ROL 14
#define LSR 15
#define ROR 15
#define IN 16
#define OUT 17
#define PUSH 18
#define POP 18
#define MOV 19
#define MVW 19
#define LDI 20
#define LDS 21
#define LD 22
#define LPM 22
#define STS 23
#define ST 24
#define CMP 25
#define CPC 25
#define CPI 26
#define BRA 27
#define CALL 28
#define RET 29
#define OUTI 30

/* Condition code definitions */
#define CCBIT 1
#define AL 0
#define EQ 1
#define NE 2
#define VS 3
#define VC 4
#define MI 5
#define PL 6
#define CS 7
#define CC 8
#define LT 9
#define GE 10
#define SH 11
#define LO 12

#endif
