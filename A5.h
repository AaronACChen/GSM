#include <stdio.h>
#include <string.h>

#define SIZE1 524287
#define SIZE2 4194303
#define SIZE3 8388607

#define OUT1 262144
#define OUT2 2097152
#define OUT3 4194304
#define MAJ1 256
#define MAJ2 1024
#define MAJ3 1024

#define B22 4194304
#define B21 2097152
#define B20 1048576
#define B18 262144
#define B17 131072
#define B16 65536
#define B13 8192
#define B7  128

typedef unsigned long reg;
typedef unsigned char byte;

typedef struct {
	reg R1; 
	reg R2; 
	reg R3;
} A5State;