TARGET_MODULE:=file_operation
dev_file:=hello-dev
obj-m:=$(TARGET_MODULE).o
BUILDSYSTEM_DIR:=/lib/modules/$(shell uname -r)/build
PWD:=$(shell pwd)

all:
	$(MAKE) -C $(BUILDSYSTEM_DIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(BUILDSYSTEM_DIR) M=$(PWD) clean
load:
	insmod ./$(TARGET_MODULE).ko
	chmod 777 /dev/$(dev_file)
unload:
	rmmod ./$(TARGET_MODULE).ko
read:
	cat /dev/$(dev_file)
write:
	echo 1 > /dev/$(dev_file)

