TRG := hello_world
SRC := $(TRG).c
MOD := $(TRG).ko
ifneq ($(KERNELRELEASE),)
obj-m := $(TRG).o
else
PWD := $(shell pwd)
KDIR := ~/linux/linux
LLVM := -21
ARCH := arm64
C_FLAGS := LLVM=$(LLVM) ARCH=$(ARCH)
FORMAT := /usr/bin/clang-format$(LLVM)
SCAN := scan-build$(LLVM) --use-cc=/usr/bin/clang$(LLVM) --use-c++=/usr/bin/clang++$(LLVM)
TIDY := /usr/bin/clang-tidy$(LLVM)
TIDY_FLAGS := -- --target=$(ARCH) $(C_FLAGS) -p .

all :
	make $(C_FLAGS) -C $(KDIR) M=$(PWD)
	$(KDIR)/scripts/clang-tools/gen_compile_commands.py
	rm -fv *.o *.mod.c *.symvers *.order *.mod .[!.]* ..[!.]*
format :
	$(FORMAT) $(SRC) -style=file -i
clean :
	rm -v $(MOD) compile_commands.json
install : $(MOD)
	sudo /sbin/insmod $(MOD)
remove :
	sudo /sbin/rmmod $(MOD)
scan :
	$(SCAN) make
tidy :
	$(TIDY) $(SRC)
endif