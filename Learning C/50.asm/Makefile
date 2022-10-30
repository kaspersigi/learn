###########################################
#Makefile for my assembler programs
###########################################
TRG = main
BIN = main.bin
OBJ = main.o
SRC = main.s
AS = /usr/bin/as
LD = /usr/bin/ld

.PHONY : all
$(TRG) : $(OBJ)
	$(LD) $(OBJ) -o $(TRG) -m elf_i386 --entry=_start
	rm -v $(OBJ)
$(OBJ) : $(SRC)
	$(AS) $(SRC) -o $(OBJ) --32
clean :
	rm -v $(TRG)
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./$(TRG)