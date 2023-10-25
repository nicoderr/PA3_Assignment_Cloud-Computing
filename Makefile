CC = gcc
CFLAGS = -Wall -O2
LIBS = -lpthread

# Name of Executable Target
TARGET = sort_program

# Source file to execute sorting
SRCS = mysort.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LIBS)

run: $(TARGET)
	./$(TARGET) input.txt output.txt log.txt

clean:
	rm -f $(TARGET)

.PHONY: all run clean
