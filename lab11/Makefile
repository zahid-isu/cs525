CC = gcc
CFLAGS = -Wall -Wextra -g
OBJECTS = main.o \
GetNumberOfNodes.o \
GenerateList.o \
Print.o \
GetKey.o \
SearchList.o \
DeleteList.o

.PHONY: clean help

main.exe: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o main.exe

%.o: %.c
	$(CC) $(FFLAGS) -c $<

clean:
	rm -f $(OBJECTS) main.exe

help:
	@echo "Valid targets:"
	@echo " main.exe"
	@echo " main.o"
	@echo " GetNumberOfNodes.o"
	@echo " GenerateList.o"
	@echo " Print.o"
	@echo " GetKey.o"
	@echo " SearchList.o"
	@echo " DeleteList.o"
	@echo " clean: removes *.o and *.exe files"
