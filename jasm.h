#ifndef OPCODE_H
#define OPCODE_H

/* size of instruction memory */
#define ROM_SIZE 65536

/* Function header to print out ROM table to a file */
void print_rom(int* ROM, FILE* f, int size);

/* Function header to determine opcode */
int decodeinst(char* inst);
int decodefunc(char* inst);

/* opcode definitions */
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

/* bit position */

#endif
