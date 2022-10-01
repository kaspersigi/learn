ifneq ($(KERNELRELEASE),)
obj-m := hello_world.o
else
PWD := $(shell pwd)
KDIR := /usr/src/linux-2.6.39.4
all:
	make -C $(KDIR) M=$(PWD)
	rm -v *.o *.mod.c *.symvers *.order
format :
	clang-format hello_world.c -style=file -i
clean:
	rm -v hello_world.ko
endif