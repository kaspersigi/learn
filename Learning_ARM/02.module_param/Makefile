TRG := hello_world
SRC := $(TRG).c
MOD := $(TRG).ko
ifneq ($(KERNELRELEASE),)
obj-m := $(TRG).o
else
PWD := $(shell pwd)
KDIR := /home/miku/Learning_ARM/linux-6.1.57
all :
	make -C $(KDIR) M=$(PWD)
	rm -rfv *.o *.mod.c *.symvers *.order *.mod .tmp_versions \.*.cmd
format :
	clang-format $(SRC) -style=file -i
clean :
	rm -v $(MOD)
install : $(MOD)
	insmod $(MOD)
remove :
	rmmod $(TRG)
show :
	dmesg
endif