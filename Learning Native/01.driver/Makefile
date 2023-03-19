TRG = hello_world
SRC = $(TRG).c
MD = $(TRG).ko
ifneq ($(KERNELRELEASE),)
obj-m := $(TRG).o
else
PWD := $(shell pwd)
KDIR := /usr/src/kernels/linux-$(shell uname -r)
all:
	make -C $(KDIR) M=$(PWD)
	rm -v *.o *.mod.c *.symvers *.order
format :
	clang-format $(SRC) -style=file -i
clean :
	rm -v $(MD)
install : $(MD)
	insmod $(MD)
remove :
	rmmod $(TRG)
show :
	dmesg
endif
