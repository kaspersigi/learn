###########################################
#Makefile for my rust programs
###########################################

TRG = main
SRC = main.rs
FLAGS = --edition 2021
DEBUG = -C debuginfo=full -C opt-level=0 -g
RELEASE = -C debuginfo=none -C opt-level=z

.PHONY : all
$(TRG) : $(SRC)
	rustc $(SRC) -o $(TRG) $(FLAGS) $(DEBUG)
format :
	rustfmt $(SRC) $(FLAGS)
clean :
	rm -v main