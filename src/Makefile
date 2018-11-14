#stjq create at 2011-08-14
BUILDTYPE=-DST_DBG_ -g -O2
LOCALTARGET = libstlib.a
CC=gcc
CPP=g++

LIBS = -L/usr/lib/ -lpthread 
CFLAGS = -I../include

#SRCS=$(wildcard ./src/*.c)
#SRCPPS +=$(wildcard ./src/*.cpp)
#SRCPPS +=$(wildcard ./src/cpp/*.cpp)

#获取所有的子目录
SRCDIRS  =  $(shell find . -maxdepth 5 -type d)
#从所有子目录中得到源代码的列表
SRCS=$(foreach ls,$(SRCDIRS),$(wildcard $(ls)/*.c))
SRCPPS=$(foreach ls,$(SRCDIRS),$(wildcard $(ls)/*.cpp))

#得到源代码对应的目标文件的列表
#OBJS=$(SRCS:.c=.o) $(SRCPPS:.s=.o)
OBJS := $(SRCS:.c=.o)
OBJS += $(SRCPPS:.cpp=.o)

%.o : %.c
	$(CC) $(CFLAGS) $(BUILDTYPE) -c $< -o $@ $(LIBS)
	@echo "compiling [$@] [$<]"

%.o : %.cpp
	$(CPP) $(CFLAGS) $(BUILDTYPE) -c $< -o $@ $(LIBS)
	@echo "compiling [$@] [$<]"

all:$(OBJS)
	ar ru ../$(LOCALTARGET) $(OBJS)  
	ranlib ../$(LOCALTARGET)
	@echo ----------------------------
	@echo target make finish
	@echo ----------------------------

clean:
	find ./ -name "*.o" | xargs rm -r
