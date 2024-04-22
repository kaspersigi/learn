###########################################
#Makefile for my rust programs
###########################################

TRG = main
SRC = main.rs
FLAGS = --edition 2021
DEBUG = -C debuginfo=full -C opt-level=0 -g
RELEASE = -C debuginfo=none -C opt-level=z

.PHONY : all
all : template
template :
	$(MAKE) -C 00.template

format :
	$(MAKE) -C 00.template format

clean :
	$(MAKE) -C 00.template clean