obj-m = driver.o

KDIR :=/home/gusdud/WSL2-Linux-Kernel-linux-msft-wsl-5.15.133.1
PWID := $(shell pwd)

default:
	make -C $(KDIR) M=$(PWD) modules

clean:
	rm -rf *.kr *.mod.* .*.cmd *.o *.ko
