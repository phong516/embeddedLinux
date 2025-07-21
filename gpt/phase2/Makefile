obj-m += chardev.o

KERNEL_DIR = /home/phong/linux-6.9

all:
	make -C $(KERNEL_DIR) M=$(PWD) modules
clean:
	make -C $(KERNEL_DIR) M=$(PWD) clean
