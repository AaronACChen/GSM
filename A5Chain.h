#include "A5.h"

A5State chainReduce(byte *outA);

A5State convertToState(unsigned long long stateB);

unsigned long long compressStateStruct(A5State state);

unsigned long long compressState(byte *outA);

int done(byte outA[15], int done);

void chain(A5State intialState, byte outA[15], int done);