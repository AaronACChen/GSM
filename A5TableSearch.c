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
		int x = 0;
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

int match(byte *a, byte *b){
	int x,match = 1;
	for (x=0;x<8;x++){
		if (a[x]!=b[x]) match = 0;
	}
	return match;
}

void tableSearch(unsigned long long initial ,int end){
	byte outA[15];
	unsigned long long initialState,outputState;
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
	outputState = compressState(outA);
	for (z=0;z<SIZE;z++){
		if (outputTable[z] == outputState){
			printf("FOUND CHAIN\n");
			printf("OUTPUT:%016llX\n",outputState);
			initialState = inputTable[z];
			printf("INPUT:%016llX\n",initialState);
		}
	}
	printf("\n");
	state = convertToState(initialState);
	A5SetState(&state);
	A5100Clock();
	A5QRun(outA);
	
	while (compressState(outA)!=initial){
		state=chainReduce(outA);
		A5SetState(&state);
		A5100Clock();
		A5QRun(outA);
	}
	initialState = compressStateStruct(state);
	printf("FOUND STATE\n");
	printf("STATE:%016llX\n",initialState);
	
	A5SetState(&state);
	A5100Clock();
	A5QRun(outA);
	printf("VERIFY:");
	for (z=0; z<8; z++) printf("%02X", outA[z]);
	printf("\n");
}

int main(int argc, char *argv[]){
	unsigned long long state;
	
	if (argc < 4) {
       fprintf(stderr,"usage %s table bitstream distinguishedPointStart\n", argv[0]);
       return -1;
    }
	
	int dp;
	dp = atoi(argv[3]);
	sscanf(argv[2],"%llX",&state);
	printf("SEARCH:%016llX\n",state);
	loadTable(argv[1]);
	tableSearch(state,dp);
}