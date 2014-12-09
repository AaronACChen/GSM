#include "A5Chain.h"

void tableCreate(int chains, int end){
	int i,z;
	A5State state;	
	srand (time(NULL));
	byte a[15];
	unsigned long long start,input,output;
	for (i = 0; i < chains; i++){
		//state=chainReduce(a);
		start = rand();
		start <<= 32;
		start |= rand();
		state = convertToState(start);
		chain(state,a,end);
		input = compressStateStruct(state);
		printf("%016llX,",input);
		output = compressState(a);
		printf("%016llX\n",output);		
	}
}

int main(int argc, char *argv[]){
	int i,z,chains,dp;
	
	if (argc < 3) {
       fprintf(stderr,"usage %s chains distinguishedPointStart\n", argv[0]);
       return -1;
    }
	chains = atoi(argv[1]);
	dp = atoi(argv[2]);
	tableCreate(chains,dp);	
}