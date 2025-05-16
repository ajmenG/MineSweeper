# Compiler configuration
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

# Directory structure
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Executable targe
TARGET = $(BIN_DIR)/mineSweeper

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default target
all: $(TARGET)

# Link executable
$(TARGET): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Run tests
test: $(TARGET)
	./$(TARGET) -t

# Clean build artifacts
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)