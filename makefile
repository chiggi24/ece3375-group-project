# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -pedantic -std=c99

# Source files
SRCS = main.c algorithm.c utility.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = main

# Default rule
all: $(TARGET)

# Compile C source files into object files
%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

# Link object files to generate the executable
$(TARGET): $(OBJS)
    $(CC) $(OBJS) -o $(TARGET)

# Clean up intermediate object files and the executable
clean:
    $(RM) $(OBJS) $(TARGET)
