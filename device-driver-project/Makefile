obj-m += src/mychardev.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	gcc src/user_app.c -o user_app

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm -f user_app

