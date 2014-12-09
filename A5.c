#include "A5.h"
reg A5R1,A5R2,A5R3;

void A5Clock1(){
	reg feedback;
	if (A5R1&B18){feedback=1;}else{feedback=0;}
	if (A5R1&B17) feedback^=1;
	if (A5R1&B16) feedback^=1;
	if (A5R1&B13) feedback^=1;
	feedback&=1;
	A5R1 = (A5R1<<1)&SIZE1;
	A5R1 |= feedback;
}

void A5Clock2(){
	reg feedback;
	if (A5R2&B21){feedback=1;}else{feedback=0;}
	if (A5R2&B20) feedback^=1;
	feedback&=1;
	A5R2 = (A5R2<<1)&SIZE2;
	A5R2 |= feedback;
}

void A5Clock3(){
	reg feedback;
	if (A5R3&B22){feedback=1;}else{feedback=0;}
	if (A5R3&B21) feedback^=1;
	if (A5R3&B20) feedback^=1;
	if (A5R3& B7) feedback^=1;
	feedback&=1;
	A5R3 = (A5R3<<1)&SIZE3;
	A5R3 |= feedback;
}

reg A5Getbit(){
	reg bit;
	if(A5R1&OUT1){bit=1;}else{bit=0;}
	if(A5R2&OUT2) bit^=1;
	if(A5R3&OUT3) bit^=1;
	return bit;
}

reg A5Majority(){
	reg majority = 0;
	if (A5R1&MAJ1) majority+=1;
	if (A5R2&MAJ2) majority+=1;
	if (A5R3&MAJ3) majority+=1;
	majority=(majority>1)?1:0;
	return majority;
}

void A5ClockAll(){
	A5Clock1();A5Clock2();A5Clock3();
}

void A5Clock(){
	reg maj = A5Majority();
	if (((A5R1&MAJ1)!=0)==maj) A5Clock1();
	if (((A5R2&MAJ2)!=0)==maj) A5Clock2();
	if (((A5R3&MAJ3)!=0)==maj) A5Clock3();
}

void A5100Clock(){
	int i;
	for (i=0; i<100; i++) {
        A5Clock();
    }
}

void A5Run(byte *A,byte *B){
	memset(A,0,sizeof(byte)*16);
	memset(B,0,sizeof(byte)*16);
	int i = 0;
	for (i=0; i<114; i++) {
		A5Clock();
		A[i/8] |= A5Getbit() << (7-(i&7));
	}
	for (i=0; i<114; i++) {
		A5Clock();
		B[i/8] |= A5Getbit() << (7-(i&7));
	}
}

void A5QRun(byte *A){
	memset(A,0,sizeof(byte)*16);

	int i = 0;
	for (i=0; i<114; i++) {
		A5Clock();
		A[i/8] |= A5Getbit() << (7-(i&7));
	}
}

void A5Setup(byte * key, reg frame){
	A5R1=A5R2=A5R3=0;
	reg keybit,framebit;
	
	int i;
	for (i=0; i<64; i++) {
		A5ClockAll();
		keybit = (key[i/8]>>(i&7))&1;
		A5R1^=keybit;A5R2^=keybit;A5R3^=keybit;
	}
	
	for (i=0; i<22; i++) {
        A5ClockAll();
        framebit = (frame>>i)&1;
        A5R1^=framebit;A5R2^=framebit;A5R3^=framebit;
    }
	
	for (i=0; i<100; i++) {
        A5Clock();
    }
}

void A5SetState(A5State * state){
	A5R1 = state->R1;
	A5R2 = state->R2;
	A5R3 = state->R3;
}

void A5GetState(A5State * state){
	state->R1 = A5R1;
	state->R2 = A5R2;
	state->R3 = A5R3;
}

int A5Bench(){
	byte key[8] = {0x12, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
	reg frame = 0x134;
	byte a[15],b[15];
	int i;
	
	for (i=0;i<1000000;i++){
		A5Setup(key,frame);
		A5Run(a,b);
	}
	for (i=0; i<15; i++)
		printf("%02hhX", a[i]);
	printf("\n");
	for (i=0; i<15; i++)
		printf("%02hhX", b[i]);
}



