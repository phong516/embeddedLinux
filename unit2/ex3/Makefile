obj-m += misc-module.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)
# 	gcc read.c -o read
# clean:
# 	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
# 	rm -rf read

# TARGET 	:= misc-module
# WARN 		:= -W -Wall -Wstrict-prototypes -Wmissing-prototypes
# INCLUDE := -isystem /lib/modules/$(uname -r)/build/include
# CFLAGS 	:= -02 -DMODULE -D__KERNEL__${WARN} ${INCLUDE}
# CC			:= gcc

# ${TARTGET}.o: ${TARGET}.c

# .PHONY: clean

# clean:
# 	rm -rf ${TARGET}.o

