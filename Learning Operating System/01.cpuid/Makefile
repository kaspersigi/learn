###########################################
#Makefile for my assembler programs
###########################################
TRG = all
EXEC = main
BIN = main.bin
OBJ = main.o
SRC = main.s
AS = /usr/bin/as
LD = /usr/bin/ld

.PHONY : all
$(TRG) : $(EXEC)
	rm -v $(OBJ)
$(EXEC) : $(OBJ)
	$(LD) $(OBJ) -o $(EXEC)
$(OBJ) : $(SRC)
	$(AS) $(SRC) -o $(OBJ)
clean :
	rm -v $(EXEC)