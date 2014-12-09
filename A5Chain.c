#include "A5Chain.h"

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

int done(byte outA[15], int end){
	int done = 0,i;
	for (i=end;i<=7;i++){
			done |= outA[i];
	}
	if (done == 0) return 1;
	return 0;
}

void chain(A5State intialState, byte outA[15], int end){
	long long count = 0,comp;
	int z;
	A5State state = intialState;
	A5SetState(&state);
	A5100Clock();
	A5QRun(outA);
	while (!done(outA, end)){
		count++;
		
		if (count == 10000){
			//printf("KEYSTREAM:");
			for (z=0; z<8; z++) printf("%02X", outA[z]);
		}
		
		state=chainReduce(outA);
		A5SetState(&state);
		A5100Clock();
		A5QRun(outA);
	}
	if (count < 10000){
		for (z=0; z<8; z++) printf("%02X", 0);
	}
	printf(",%d,",count);
}
