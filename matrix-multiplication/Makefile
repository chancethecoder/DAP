CC = gcc
CFLAGS = -W -std=c99 -pg
TARGET_CPU_EXAMPLE = cpu_practice_exe
OBJECT_CPU_EXAMPLE = matrix_product_practice_cpu.o

all: clean $(TARGET_CPU_EXAMPLE)

$(TARGET_CPU_EXAMPLE): $(OBJECT_CPU_EXAMPLE)
	$(CC) $(CFLAGS) -o $@ $^

clean: FORCE
	rm -f *.o *_exe *.out *.txt
FORCE: