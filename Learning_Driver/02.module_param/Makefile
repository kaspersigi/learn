TRG := hello_world
SRC := $(TRG).c
MOD := $(TRG).ko
ifneq ($(KERNELRELEASE),)
obj-m := $(TRG).o
else
PWD := $(shell pwd)
KDIR := ~/linux/linux
LLVM := -20
ARCH := arm64
C_FLAGS := LLVM=$(LLVM) ARCH=$(ARCH)
FORMAT = /usr/bin/clang-format$(LLVM)

all :
	make $(C_FLAGS) -C $(KDIR) M=$(PWD)
	rm -fv *.o *.mod.c *.symvers *.order *.mod .[!.]* ..[!.]*
format :
	$(FORMAT) $(SRC) -style=file -i
clean :
	rm -v $(MOD)
install : $(MOD)
	sudo /sbin/insmod $(MOD)
remove :
	sudo /sbin/rmmod $(MOD)
endif