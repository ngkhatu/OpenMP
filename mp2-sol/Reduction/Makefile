CC = ~/Bin/gcc43
CFLAGS = -fopenmp

LIB = -lm -lc

UNITFILES = 

#------------ EXECUTABLE FILES : MOSTLY EXPERIMENTS ---------------

reduce : reduce.o $(UNITFILES)
	$(CC) $(CFLAGS) -o reduce reduce.o $(UNITFILES) $(LIB)

clean:
	rm -f core reduce *.o

reduce.o : reduce.c
	$(CC) $(CFLAGS) -c reduce.c $(INCLUDE) 


