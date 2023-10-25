CC = gcc
CFLAGS = -Wall -O2
LIBS = -lpthread

# Target executable name
TARGET = sort_program

# Source files
SRCS = mysort.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LIBS)

run: $(TARGET)
	./$(TARGET) input.txt output.txt log.txt

clean:
	rm -f $(TARGET)

.PHONY: all run clean

