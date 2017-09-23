CC = gcc
CFLAGS = -std=c99
LIBS = 
TARGET = main
OBJECT = main.c
OS := $(shell uname)

ifeq ($(OS), Linux)
	LIBS += -lOpenCL
endif
ifeq ($(OS), Darwin)
	LIBS += -framework OpenCL
endif

all: clean $(TARGET)

$(TARGET): $(OBJECT)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean: FORCE
	rm -rf *.o main *.out
FORCE:
