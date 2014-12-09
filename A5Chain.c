#include "A5.h"

#define SIZE 5
long long input[SIZE];
long long output[SIZE];

A5State chainReduce(byte *outA){
	unsigned long long stateB = 0;
	A5State state;
	int i;
	for (i=0; i<7; i++){
		stateB |= outA[i];
		stateB = stateB << 8;
	}
	stateB |= outA[7];
	state.R1 = stateB>>45;
	state.R2 = stateB>>23;
	state.R2&=SIZE2;
	state.R3 = stateB;
	state.R3&=SIZE3;
	return state;
}

A5State convertToState(unsigned long long stateB){
	A5State state;
	int i;
	state.R1 = stateB>>45;
	state.R2 = stateB>>23;
	state.R2&=SIZE2;
	state.R3 = stateB;
	state.R3&=SIZE3;
	return state;
}

unsigned long long compressStateStruct(A5State state){
	unsigned long long compress=0;
	compress |= state.R1;
	compress<<=22;
	compress |= state.R2;
	compress<<=23;
	compress |= state.R3;
	return compress;
}

unsigned long long compressState(byte *outA){
	unsigned long long compress=0;
	int i,z;
	for (i=0; i<7; i++){
		compress |= outA[i];
		compress <<= 8;
	}
	compress |= outA[7];
	return compress;
}

int done(byte outA[15]){
	int done = 0,i;
	for (i=6;i<=7;i++){
			done |= outA[i];
	}
	if (done == 0) return 1;
	return 0;
}

void chain(A5State intialState, byte outA[15]){
	long long count = 0,comp;
	int z;
	A5State state = intialState;
	A5SetState(&state);
	A5100Clock();
	A5QRun(outA);
	while (!done(outA)){
		count++;
		/*
		if (count == 10000){
			//printf("KEYSTREAM:");
			for (z=0; z<8; z++) printf("%02X", outA[z]);
			printf(",");
		}
		*/
		state=chainReduce(outA);
		A5SetState(&state);
		A5100Clock();
		A5QRun(outA);
	}
	printf("%d,",count);
}

void tableCreate(){
	int i,z;
	A5State state;
	byte a[15] = {0x12, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
	for (i = 0; i < 10; i++){
		//key[0]=i;
		state=chainReduce(a);
		chain(state,a);

		input[1] = compressStateStruct(state);
		printf("%016llX,",input[1]);
		output[1] = compressState(a);
		printf("%016llX\n",output[1]);
		
	}
}



void tableSearch(){
	byte outA[15];
	long long initial = 0x477CBAA0E3943D9B;
	int z;
	A5State state;
	state = convertToState(initial);
	A5SetState(&state);
	A5100Clock();
	A5QRun(outA);
	while (!done(outA)){
		state=chainReduce(outA);
		A5SetState(&state);
		A5100Clock();
		A5QRun(outA);
	}
	printf("OUTPUT:");
	for (z=0; z<8; z++) printf("%02X", outA[z]);
	
	unsigned long long compress = compressState(outA);
	for (z=0;z<SIZE;z++){
		if (output[z]==compress){
			printf("\nINPUT:%016llX\n",input[z]);
			state = convertToState(input[z]);
			printf("State:%u %u %u \n",state.R1,state.R2,state.R3);
			initial = input[z];
			break;
		}
	}
	
	state = convertToState(input[z]);
	//printf("State:%u %u %u \n",state.R1,state.R2,state.R3);
	A5SetState(&state);
	A5100Clock();
	A5QRun(outA);
	while (!done(outA)){
		if (compressState(outA) == 0x477CBAA0E3943D9B){
			printf("WINNER:%016llX\n",compressStateStruct(state));
		}
		state=chainReduce(outA);
		A5SetState(&state);
		A5100Clock();
		A5QRun(outA);
	}
	for (z=0; z<8; z++) printf("%02X", outA[z]);	
}

int main(){
	byte key[8] = {0x12, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
	reg frame = 0x134;
	byte a[15];byte b[15];
	A5State state;
	int i,z;
	A5Setup(key,frame);
	A5Run(a,b);
	A5GetState(&state);
		
	tableCreate();
	//tableSearch();
	//A5Setup(key,frame);
		
	printf("\n\n");
	return;
	for (i=0; i<15; i++)
		printf("%02X", a[i]);
	printf("\n");
	char t[4];
	long tt[4];
	
}