CC = mpicc
FFLAGS = -O3 -Wall -std=c99 
LFLAGS = 

OBJECTS = norm.o matrix.o

main.exe: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -lm -o norm.exe

%.o: %.c
	$(CC) $(FFLAGS) -c $<

clean :
	rm -f $(OBJECTS) *.exe
