CC = gcc
CFLAGS = -std=c99
LIBS = -lm
OBJECT1 = cpu_test.c timer.c
OBJECT2 = gpu_test.c timer.c
OS := $(shell uname)

ifeq ($(OS), Linux)
	LIBS += -lOpenCL
endif
ifeq ($(OS), Darwin)
	LIBS += -framework OpenCL
endif

all: clean cpu_test gpu_test

cpu_test: $(OBJECT1)
	$(CC) $(CFLAGS) -o cpu_test $(OBJECT1) $(LIBS)

gpu_test: $(OBJECT2)
	$(CC) $(CFLAGS) -o gpu_test $(OBJECT2) $(LIBS)

clean: FORCE
	rm -rf *.o cpu_test gpu_test *.out
FORCE:
