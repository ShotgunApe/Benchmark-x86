# Variables
CC = gcc
CFLAGS = -Wall -g
SOURCES = main.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = time

# Default target
all: $(EXECUTABLE)

# Compile object files
$(OBJECTS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create executable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)