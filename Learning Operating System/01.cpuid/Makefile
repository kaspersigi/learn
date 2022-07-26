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
DUMP = /usr/bin/objcopy
AS_FLAGS = --32

.PHONY : all
$(TRG) : $(EXEC)
	$(DUMP) $(OBJ) -O binary $(BIN)
	rm -v $(OBJ)
	rm -v $(BIN)
$(EXEC) : $(OBJ)
	$(LD) $(OBJ) -o $(EXEC)
$(OBJ) : $(SRC)
	$(AS) $(SRC) -o $(OBJ)
clean :
	rm -v $(EXEC)