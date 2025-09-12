# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -Iinclude -O2

# Directories
SRC_DIR := src
OBJ_DIR := build
BIN_DIR := bin

# Target executable name
TARGET := $(BIN_DIR)/cire

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Default target
all: $(TARGET)

# Link objects into the final binary
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $(TARGET)
	@echo "Build successful: $(TARGET)"

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Run the compiled program
run: all
	$(TARGET)

.PHONY: all clean run

