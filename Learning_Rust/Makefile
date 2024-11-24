###########################################
#Makefile for my rust programs
###########################################

TRG = main
SRC = main.rs
FLAGS = --edition 2021
DEBUG = -C debuginfo=full -C opt-level=0 -g
RELEASE = -C debuginfo=none -C opt-level=z

.PHONY : all
all : template print format_print struct
template :
	$(MAKE) -C 00.template
print :
	$(MAKE) -C 01.print
format_print :
	$(MAKE) -C 02.format_print
struct :
	$(MAKE) -C 03.struct

format :
	$(MAKE) -C 00.template format
	$(MAKE) -C 01.print format
	$(MAKE) -C 02.format_print format
	$(MAKE) -C 03.struct format

clean :
	$(MAKE) -C 00.template clean
	$(MAKE) -C 01.print clean
	$(MAKE) -C 02.format_print clean
	$(MAKE) -C 03.struct clean