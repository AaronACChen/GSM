#include "A5.h"
#define SIZE 1000

long long inputTable[SIZE];
long long outputTable[SIZE];

A5State chainReduce(byte *outA);
A5State convertToState(unsigned long long stateB);

void loadTable(){
		unsigned long long input,output;
		FILE *fp;
		fp = fopen("TABLE","r");
		int x;
		while(fscanf(fp,"%*llX,%*d,%llX,%llX,\n",&input,&output)!=EOF){
			//fscanf(fp,"%*llX,%*d,%llX,%llX,\n",&input,&output);
			//printf("%016llX,%016llX\n",input,output);
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

int main(){
	/*
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
	*/
	loadTable();
	
}