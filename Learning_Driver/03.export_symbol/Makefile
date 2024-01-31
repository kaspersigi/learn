TRG := hello_world
SRC := $(TRG).c
MOD := $(TRG).ko
ifneq ($(KERNELRELEASE),)
obj-m := $(TRG).o
else
PWD := $(shell pwd)
KDIR := ~/linux/linux
C_FLAGS := LLVM=1
all :
	make $(C_FLAGS) -C $(KDIR) M=$(PWD)
	rm -rfv *.o *.mod.c *.order *.mod .tmp_versions \.*.cmd \.*d
format :
	clang-format $(SRC) -style=file -i
clean :
	rm -v $(MOD) Module.symvers
install : $(MOD)
	sudo /usr/sbin/insmod $(MOD)
remove :
	sudo /usr/sbin/rmmod $(MOD)
endif