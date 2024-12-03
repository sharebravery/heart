# Default compiler
CC = gcc
CFLAGS = -Wall -I./src/inc
LDFLAGS =

# Cross-compiler
CROSS_CC = aarch64-linux-gnu-gcc
CROSS_CFLAGS = -Wall -I./src/inc
CROSS_LDFLAGS = -static

# Define source code directories
SRC_DIR = src
BUILD_DIR = build
CROSS_BUILD_DIR = cross_build

# Recursively find all source files (including .c files in subdirectories)
SRCS = $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
CROSS_OBJS = $(patsubst $(SRC_DIR)/%.c,$(CROSS_BUILD_DIR)/%.o,$(SRCS))

# Define target files
TARGET = main_program
TARGET_PROGRAM = $(BUILD_DIR)/$(TARGET)
CROSS_TARGET_PROGRAM = $(CROSS_BUILD_DIR)/$(TARGET)

# Default target
all: $(TARGET_PROGRAM) $(CROSS_TARGET_PROGRAM)

# Build the target program
$(TARGET_PROGRAM): $(OBJS)
	@echo "Building the default combined program..."
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)

# Cross-compile the target program
$(CROSS_TARGET_PROGRAM): $(CROSS_OBJS)
	@echo "Building the cross-compiled combined program..."
	$(CROSS_CC) $(CROSS_CFLAGS) $(CROSS_LDFLAGS) -o $@ $(CROSS_OBJS)

# Compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)  # Create the directory for the target file
	@echo "Compiling $< ..."
	$(CC) $(CFLAGS) -c -o $@ $<

# Cross-compile source files into object files
$(CROSS_BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)  # Create the directory for the target file
	@echo "Cross-compiling $< ..."
	$(CROSS_CC) $(CROSS_CFLAGS) -c -o $@ $<

# Clean the build files
clean:
	@echo "Cleaning the build directories..."
	rm -rf $(BUILD_DIR)
	rm -rf $(CROSS_BUILD_DIR)

# Declare phony targets
.PHONY: all clean
