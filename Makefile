# Kompilator i flagi
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

# Katalogi
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Plik wykonywalny
TARGET = $(BIN_DIR)/saper

# Pliki źródłowe i obiektowe
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Domyślny cel
all: $(TARGET)

# Linkowanie pliku wykonywalnego
$(TARGET): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Kompilacja plików źródłowych do obiektowych
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Cel testowy
test: $(TARGET)
	./$(TARGET) -t

# Czyszczenie plików obiektowych i pliku wykonywalnego
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
