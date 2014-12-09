build with ./make all

Implementation of the A5/1 Cipher and time-memory tradeoff table using distinguished points.


Table Generation is done using the command A5BuildTable:

	./A5BuildTable numberofchains firstBlockOfDistinguishedPoints

	i.e
	./A5BuildTable 1000 6

	Will build a table of 1000 chains where the first byte of necessary zeroes is byte 6, meaning there is at least 2-bytes (8-6) of trailing zeroes. All byte parameters are in hexadecimal.

Table Lookup is done using the command A5TableSearch:

	./A5BuildTable table cipherstream firstBlockOfDistinguishedPoints

	i.e 
	./A5TableSearch TABLE06-1 E06F5BD7BD5BDBFD 6

	Will search through the given table to find the initial state for the given ciphertext where the firstBlockOfDistinguishedPoints is the DistinguishedPoint parameter the table was generated with. All byte parameters are in hexadecimal.


Table Format
	
	Table format is currently not space efficient for debugging and testing purposes. Each line consists of:
	test cipher stream, length of chain, chain start, chain end.

	Example table names are named using the DistinguishedPoint parameter used in generating it:
	TABLE06-1 was generated using a DistinguishedPointByte of 6.
	
Backclocking is done using the command A5Backclock:

	./A5Backclock initialState
	
	i.e.
	./A5Backclock AC524EC409CA8EAE
	
	Will return a backclocked cipher state without the 22-bit frame. All byte parameters are in hexadecimal.

Decryption is done using the command A5Decrypt:

	./A5Decrypt backclockedCipherState frameID ciphertextBurstA ciphertextBurstB
	
	ie.
	./A5Decrypt D7E001B102363E4E 134 534EAA582FE8151AB6E1855A728C00 24FD35A35D5FB6526D32F906DF1AC0
	
	Will return the 224-bit plaintext of the burst. All byte parameters are in hexadecimal.

