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
reg R1,R2,R3;

void clock1(){
	reg feedback;
	if (R1&B18){feedback=1;}else{feedback=0;}
	if (R1&B17) feedback^=1;
	if (R1&B16) feedback^=1;
	if (R1&B13) feedback^=1;
	feedback&=1;
	R1 = (R1<<1)&SIZE1;
	R1 |= feedback;
}

void clock2(){
	reg feedback;
	if (R2&B21){feedback=1;}else{feedback=0;}
	if (R2&B20) feedback^=1;
	feedback&=1;
	R2 = (R2<<1)&SIZE2;
	R2 |= feedback;
}

void clock3(){
	reg feedback;
	if (R3&B22){feedback=1;}else{feedback=0;}
	if (R3&B21) feedback^=1;
	if (R3&B20) feedback^=1;
	if (R3& B7) feedback^=1;
	feedback&=1;
	R3 = (R3<<1)&SIZE3;
	R3 |= feedback;
}

reg getbit(){
	reg bit;
	if(R1&OUT1){bit=1;}else{bit=0;}
	if(R2&OUT2) bit^=1;
	if(R3&OUT3) bit^=1;
	return bit;
}

reg majority(){
	reg majority = 0;
	if (R1&MAJ1) majority+=1;
	if (R2&MAJ2) majority+=1;
	if (R3&MAJ3) majority+=1;
	majority=(majority>1)?1:0;
	return majority;
}

void clockAll(){
	clock1();clock2();clock3();
}

void clock(){
	reg maj = majority();
	if (((R1&MAJ1)!=0)==maj) clock1();
	if (((R2&MAJ2)!=0)==maj) clock2();
	if (((R3&MAJ3)!=0)==maj) clock3();
}

void run(byte *A,byte *B){
	memset(A,0,sizeof(byte)*16);
	memset(B,0,sizeof(byte)*16);
	int i = 0;
	for (i=0; i<114; i++) {
		clock();
		A[i/8] |= getbit() << (7-(i&7));
	}
	for (i=0; i<114; i++) {
		clock();
		B[i/8] |= getbit() << (7-(i&7));
	}
}

void setup(reg key[8], reg frame){
	R1=R2=R3=0;
	reg keybit,framebit;
	
	int i;
	for (i=0; i<64; i++) {
		clockAll();
		keybit = (key[i/8]>>(i&7))&1;
		R1^=keybit;R2^=keybit;R3^=keybit;
	}
	
	for (i=0; i<22; i++) {
        clockAll();
        framebit = (frame>>i)&1;
        R1^=framebit;R2^=framebit;R3^=framebit;
    }
	
	for (i=0; i<100; i++) {
        clock();
    }
}

int main(){
	reg key[8] = {0x12, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
	reg frame = 0x134;
	byte a[15],b[15];
	int i;
	
	for (i=0;i<1000000;i++){
		setup(key,frame);
		run(a,b);
	}
	for (i=0; i<15; i++)
		printf("%02hhX", a[i]);
	printf("\n");
	for (i=0; i<15; i++)
		printf("%02hhX", b[i]);
}



