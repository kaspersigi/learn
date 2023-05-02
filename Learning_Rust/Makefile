###########################################
#Makefile for my rust programs
###########################################

TRG = main
SRC = main.rs
FLAGS = --edition 2021
DEBUG = -g -C opt-level=0
RELEASE = -C debuginfo=0 -C opt-level=3

.PHONY : all
all : template
template :
	$(MAKE) -C 00.template

format :
	$(MAKE) -C 00.template format

clean :
	$(MAKE) -C 00.template clean