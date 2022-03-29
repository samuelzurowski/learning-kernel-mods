obj-m += hello-1.o

KVERSION = $(shell uname -r)

all: 
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) clean

test:
	sudo dmesg -C
	sudo insmod hello-1.ko
	sudo rmmod hello-1.ko
	dmesg
