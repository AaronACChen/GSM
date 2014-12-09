OBJ = A5.o A5Chain.o

CC=gcc
CFLAGS =-O3

all: A5TableBuild A5TableSearch
	

A5TableBuild: $(OBJ) A5TableBuild.c
	$(CC) $(CFLAGS) -o A5TableBuild $(OBJ) A5TableBuild.c

A5TableSearch: $(OBJ) A5TableSearch.c
	$(CC) $(CFLAGS) -o A5TableSearch $(OBJ) A5TableSearch.c
	
A5.o: A5.c
	$(CC) $(CFLAGS) -c A5.c

A5Chain.o : A5Chain.c
	$(CC) $(CFLAGS) -c A5Chain.c

clean:
	rm -f $(OBJ)
