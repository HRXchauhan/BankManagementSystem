CC = gcc
CFLAGS = -Wall -Iinclude
SRC = src/main.c src/bst.c src/sort_search.c src/stack.c src/queue.c src/file_ops.c
TARGET = bank_system

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
