CC = gcc
CFLAGS = -W -Wall -std=c99 -pg
TARGET_CPU_EXAMPLE = cpu_practice
OBJECT_CPU_EXAMPLE = matrix_product_practice_cpu.o
GPROF_OUTPUT = gmon.out
GPROF_LOG = log.txt

all: $(TARGET_CPU_EXAMPLE)

$(TARGET_CPU_EXAMPLE): $(OBJECT_CPU_EXAMPLE)
	$(CC) $(CFLAGS) -o $@ $^ ; \
	for number in 5000 10000 15000 20000 25000 ; do \
		./$(TARGET_CPU_EXAMPLE) $$number ; \
		gprof -b $(TARGET_CPU_EXAMPLE) $(GPROF_OUTPUT) >> $(GPROF_LOG) ; \
		echo "\n\n\n==========================\n\n\n" >> $(GPROF_LOG) ; \
	done ;

clean:
	rm *.o *_practice *.out *.txt