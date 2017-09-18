CC = gcc
CFLAGS =-std=c99 -pg
TARGET_CPU_INT_EXAMPLE = cpu_integer_exe
OBJECT_CPU_INT_EXAMPLE = cpu_integer.o
TARGET_CPU_FLOAT_EXAMPLE = cpu_float_exe
OBJECT_CPU_FLOAT_EXAMPLE = cpu_float.o

all: clean $(TARGET_CPU_INT_EXAMPLE) $(TARGET_CPU_FLOAT_EXAMPLE)

$(TARGET_CPU_INT_EXAMPLE): $(OBJECT_CPU_INT_EXAMPLE)
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET_CPU_FLOAT_EXAMPLE): $(OBJECT_CPU_FLOAT_EXAMPLE)
	$(CC) $(CFLAGS) -o $@ $^

clean: FORCE
	rm -rf *.o *_exe *.out log*
FORCE:
