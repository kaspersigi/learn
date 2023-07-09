TRG := hello_world
SRC := $(TRG).c
MOD := $(TRG).ko
ifneq ($(KERNELRELEASE),)
obj-m := $(TRG).o
else
PWD := $(shell pwd)
KDIR := /usr/src/kernels/linux-$(shell uname -r)
all :
	make -C $(KDIR) M=$(PWD)
	rm -rfv *.o *.mod.c *.order *.mod .tmp_versions \.*.cmd \.*d
format :
	clang-format $(SRC) -style=file -i
clean :
	rm -v $(MOD)
	rm -v Module.symvers
install : $(MOD)
	insmod $(MOD)
remove :
	rmmod $(TRG)
show :
	dmesg
endif