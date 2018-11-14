#stjq create at 2011-08-14
LOCALTARGET = libstlib.a

LIBS = -L/usr/lib/ -lpthread 
CFLAGS = -Iinclude

all:$(OBJS)
	make -C src 
	make CPPTEST all -C test


clean:
	rm $(LOCALTARGET)
	make -C src clean
	make -C test clean

