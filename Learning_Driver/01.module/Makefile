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
	rm -rfv *.o *.mod.c *.symvers *.order *.mod .tmp_versions \.*.cmd
format :
	clang-format $(SRC) -style=file -i
clean :
	rm -v $(MOD)
install : $(MOD)
	/usr/sbin/insmod $(MOD)
remove :
	/usr/sbin/rmmod $(MOD)
endif