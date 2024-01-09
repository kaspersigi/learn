TRG := hello_world
SRC := $(TRG).c
MOD := $(TRG).ko
ifneq ($(KERNELRELEASE),)
obj-m := $(TRG).o
else
PWD := $(shell pwd)
KDIR := ~/linux/linux
PLATFORM := ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
all :
	make -C $(KDIR) M=$(PWD)
	rm -rfv *.o *.mod.c *.symvers *.order *.mod .tmp_versions \.*.cmd
format :
	clang-format $(SRC) -style=file -i
clean :
	rm -v $(MOD)
install : $(MOD)
	cp $(MOD) ~/linux/_fs
remove :
	rm ~/linux/_fs/$(MOD)
endif