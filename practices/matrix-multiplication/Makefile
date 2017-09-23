CC = gcc
CFLAGS = -std=c99
TARGET = main
OBJECT = main.c

all: clean $(TARGET)

$(TARGET): $(OBJECT)
	$(CC) $(CFLAGS) -o $@ $^ -framework OpenCL

clean: FORCE
	rm -rf *.o main *.out
FORCE:
