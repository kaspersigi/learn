###########################################
#Makefile for my assembler programs
###########################################

TRG = main.bin
EXEC = main
OBJ = main.o
SRC = main.s
AS = /usr/bin/as
LD = /usr/bin/ld
DUMP = /usr/bin/objcopy
AS_FLAGS = --32

.PHONY : all
$(TRG) : $(EXEC)
	$(DUMP) $(OBJ) -O binary $(TRG)
	rm -v $(EXEC) $(OBJ)
$(EXEC) : $(OBJ)
	$(LD) $(OBJ) -o $(EXEC)
$(OBJ) : $(SRC)
	$(AS) $(SRC) -o $(OBJ) $(AS_FLAGS)
clean :
	rm -v $(TRG)