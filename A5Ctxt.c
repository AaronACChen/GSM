#include "A5.h"

void clock1(A5_Ctxt * ctxt){
	reg feedback;
	if (ctxt->R1&B18){feedback=1;}else{feedback=0;}
	if (ctxt->R1&B17) feedback^=1;
	if (ctxt->R1&B16) feedback^=1;
	if (ctxt->R1&B13) feedback^=1;
	feedback&=1;
	ctxt->R1 = (ctxt->R1<<1)&SIZE1;
	ctxt->R1 |= feedback;
}

void clock2(A5_Ctxt * ctxt){
	reg feedback;
	if (ctxt->R2&B21){feedback=1;}else{feedback=0;}
	if (ctxt->R2&B20) feedback^=1;
	feedback&=1;
	ctxt->R2 = (ctxt->R2<<1)&SIZE2;
	ctxt->R2 |= feedback;
}

void clock3(A5_Ctxt * ctxt){
	reg feedback;
	if (ctxt->R3&B22){feedback=1;}else{feedback=0;}
	if (ctxt->R3&B21) feedback^=1;
	if (ctxt->R3&B20) feedback^=1;
	if (ctxt->R3& B7) feedback^=1;
	feedback&=1;
	ctxt->R3 = (ctxt->R3<<1)&SIZE3;
	ctxt->R3 |= feedback;
}

reg getbit(A5_Ctxt * ctxt){
	reg bit;
	if(ctxt->R1&OUT1){bit=1;}else{bit=0;}
	if(ctxt->R2&OUT2) bit^=1;
	if(ctxt->R3&OUT3) bit^=1;
	return bit;
}

reg majority(A5_Ctxt * ctxt){
	reg majority = 0;
	if (ctxt->R1&MAJ1) majority+=1;
	if (ctxt->R2&MAJ2) majority+=1;
	if (ctxt->R3&MAJ3) majority+=1;
	majority=(majority>1)?1:0;
	return majority;
}

void clockAll(A5_Ctxt * ctxt){
	clock1(ctxt);clock2(ctxt);clock3(ctxt);
}

void clock(A5_Ctxt * ctxt){
	reg maj = majority(ctxt);
	if (((ctxt->R1&MAJ1)!=0)==maj) clock1(ctxt);
	if (((ctxt->R2&MAJ2)!=0)==maj) clock2(ctxt);
	if (((ctxt->R3&MAJ3)!=0)==maj) clock3(ctxt);
}

void run(A5_Ctxt * ctxt,byte *A,byte *B){
	memset(A,0,sizeof(byte)*16);
	memset(B,0,sizeof(byte)*16);
	
	int i = 0;
	for (i=0; i<114; i++) {
		clock(ctxt);
		A[i/8] |= getbit(ctxt) << (7-(i&7));
	}
	for (i=0; i<114; i++) {
		clock(ctxt);
		B[i/8] |= getbit(ctxt) << (7-(i&7));
	}
}

void run64(A5_Ctxt * ctxt,byte *A){
	memset(A,0,sizeof(byte)*8);
	int i = 0;
	for (i=0; i<114; i++) {
		clock(ctxt);
		A[i/8] |= getbit(ctxt) << (7-(i&7));
	}
}

void setup(A5_Ctxt * ctxt,reg key[8], reg frame){
	ctxt->R1=ctxt->R2=ctxt->R3=0;
	reg keybit,framebit;
	int i;
	for (i=0; i<64; i++) {
		clockAll(ctxt);
		keybit = (key[i/8]>>(i&7))&1;
		ctxt->R1^=keybit;ctxt->R2^=keybit;ctxt->R3^=keybit;
	}
	for (i=0; i<22; i++) {
        clockAll(ctxt);
        framebit = (frame>>i)&1;
        ctxt->R1^=framebit;ctxt->R2^=framebit;ctxt->R3^=framebit;
    }
	for (i=0; i<100; i++) {
        clock(ctxt);
    }
}

int main(){
	reg key[8] = {0x12, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
	reg frame = 0x134;
	byte a[15];byte b[15];
	A5_Ctxt ctxt;
	int i;
	for (i=0;i<1000000;i++){
		setup(&ctxt,key,frame);
		run(&ctxt,a,b);	
	}
	
	for (i=0; i<15; i++)
		printf("%02X", a[i]);
	printf("\n");
	for (i=0; i<15; i++)
		printf("%02X", b[i]);
}



