obj-m += chardev.o

KERNEL_DIR = /home/phong/linux

all:
	make -C $(KERNEL_DIR) M=$(PWD) modules
clean:
	make -C $(KERNEL_DIR) M=$(PWD) clean
