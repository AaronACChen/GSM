#include "A5.h"

A5State chainReduce(byte outA[15]){
	unsigned long long stateB = 0;
	A5State state;
	int i;
	
	for (i=0; i<7; i++){
		stateB |= outA[i];
		stateB <<= 8;
	}
	stateB |= outA[7];
	stateB += 1;
	//printf("%016llX\n", stateB);
		
	//stateB &= 0xFFFFFFFF00000000;
	//printf("%016llX\n", stateB);
	
	//printf("\n");
	
	state.R1 = stateB>>45;
	//printf("%016llX\n", state.R1);
	
	state.R2 = stateB>>23;
	state.R2&=SIZE2;
	//printf("%016llX\n", state.R2);
	
	state.R3 = stateB;
	state.R3&=SIZE3;
	//printf("%016llX\n", state.R3);
	
	
	return state;
}

int main(){
	//reg key[8] = {0x12, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
	//reg key[8] = {0x12, 0x23, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00};
	reg key[8] = {0x12, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xFF};
	reg frame = 0x134;
	byte a[15];byte b[15];
	A5State state;
	int i,z;
	A5Setup(key,frame);
	A5Run(a,b);
	int done = 1;
	long long count = 0;
	while (done){
		count++;
		if ((count&1048575)==1048575){
			printf(" %d \n",count);
		}
		done = 0;
		for (i=11;i<=14;i++){
			done |= a[i];
		}
		//for (z=0; z<15; z++) printf("%02X", a[z]);
		//printf(" %0d",a[7]);
		//printf("\n");
		state=chainReduce(a);
		A5SetState(&state);
		A5Run(a,b);
	}
	
	//A5Setup(key,frame);
		
	printf("\n\n");
	
	for (i=0; i<15; i++)
		printf("%02X", a[i]);
	printf("\n");
	for (i=0; i<15; i++)
		printf("%02X", b[i]);
	printf("\n");
	char t[4];
	long tt[4];
	
}