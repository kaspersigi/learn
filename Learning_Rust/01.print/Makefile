###########################################
#Makefile for my rust programs
###########################################

TRG = main
SRC = main.rs
FLAGS = --edition 2021
DEBUG = -g -C opt-level=0
RELEASE = -C debuginfo=0 -C opt-level=3

.PHONY : all
$(TRG) : $(SRC)
	rustc $(SRC) -o $(TRG) $(FLAGS) $(DEBUG)
format :
	rustfmt $(SRC) $(FLAGS)
clean :
	rm -v main