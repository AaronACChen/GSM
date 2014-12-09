#include "A5Chain.h"

void input(char in[], unsigned long long *out){
	int x;
	unsigned long long temp,test;
	
	char buf[3];
	test = 0;
	out[1] = 0;
	
	for (x=0;x<7;x++){
		memcpy(buf,in+(x*2),2);
		buf[2] = 0;
		sscanf(buf,"%X",&temp);
		printf("%s %02X ",buf, temp);

		test |= 1;
		test <<= 8;
		printf("\n%016llX\n",test);
	}
	memcpy(buf,in+(x*2),2);
	buf[2] = 0;
	sscanf(buf,"%X",&temp);
	printf("%s %X ",buf, temp);
	test |= temp;
	
	printf("\n%016llX\n",test);
	
	/*
	out[1] = 0;
	for (x=8;x<16;x++){
		memcpy(buf,in+(x*2),2);
		buf[2] = 0;
		sscanf(buf,"%X",&temp);

		out[1] |= temp;
		out[1] <<= 8;
	}
	*/
	
}

int main(int argc, char *argv[]){
	if (argc < 5) {
       fprintf(stderr,"usage %s backclockedCipherState frameID ciphertextBurstA ciphertextBurstB\n", argv[0]);
       return -1;
    }
	reg frame;
	unsigned long long state;
	
	unsigned long long A[2];
	unsigned long long B[2];
	
	sscanf(argv[1],"%llX",&state);
	sscanf(argv[2],"%X",&frame);
	input(argv[3],A);
	//input(argv[4],B);
	printf("\n%016llX\n",A[0]);	

}