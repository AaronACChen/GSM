#include "A5Chain.h"
#define SIZE 1000

long long inputTable[SIZE];
long long outputTable[SIZE];

A5State chainReduce(byte *outA);
A5State convertToState(unsigned long long stateB);

void loadTable(char * table){
		unsigned long long input,output;
		FILE *fp;
		fp = fopen(table,"r");
		int x;
		while(fscanf(fp,"%*llX,%*d,%llX,%llX,\n",&input,&output)!=EOF){
			inputTable[x] = input;
			outputTable[x] = output;
			x++;
		}
		for (x=0;x<1000;x++){
			//printf("%016llX,%016llX\n",inputTable[x],outputTable[x]);
		}
		printf("TABLE LOADED \n",input,output);
		fclose(fp);
}

void tableSearch(int end){
	byte outA[15];
	long long initial = 0xCAE40D5E841B68C7;
	long long initialState;
	int z;
	A5State state;
	state = convertToState(initial);
	A5SetState(&state);
	A5100Clock();
	A5QRun(outA);
	while (!done(outA,end)){
		state=chainReduce(outA);
		A5SetState(&state);
		A5100Clock();
		A5QRun(outA);
	}
	printf("OUTPUT:");
	for (z=0; z<8; z++) printf("%02X", outA[z]);
	printf("\n");
	
	initialState = compressStateStruct(state);
	printf("\nSTATE:%016llX\n",initialState);
	
	/*
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
	*/
}

int main(int argc, char *argv[]){
	int dp;
	dp = atoi(argv[2]);
	loadTable(argv[1]);
	tableSearch(dp);
}