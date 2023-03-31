CC = gcc
FFLAGS = -Wall -std=c99 -fopenmp 
LFLAGS = -lgomp

OBJECTS = main.o \
matrix.o\

main.exe: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -lm -o main.exe

%.o: %.c
	$(CC) $(FFLAGS) -c $<

clean :
	rm -f $(OBJECTS) *. exe
