BUILDTYPE=-DST_DBG_ -g -O2
LIBS = -L/usr/lib/ -lpthread -L../ -lstlib
CFLAGS = -I../include
TARGET = sttest.exe
TARGETCPP = sttest_cpp.exe
CPP = g++
CC = gcc

SRCS=$(wildcard ./*.c)
SRCPP=$(wildcard ./*.cpp)

#OBJS := $(SRCS:.c=.o)



all:$(SRCS)
	$(CC) -o $(TARGET) $<  $(CFLAGS) $(LIBS) -g

CPPTEST:$(SRCPP)
	$(CPP) -o $(TARGETCPP) $<  $(CFLAGS) $(LIBS) -g

clean:
	rm $(TARGET) $(TARGETCPP)
	
