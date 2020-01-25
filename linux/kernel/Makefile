obj-m := Hello_Kernel_Module.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test:
	sudo dmesg -C
	sudo insmod Hello_Kernel_Module.ko
	sudo rmmod Hello_Kernel_Module.ko
	dmesg

