# Compiler and flags
CC = gcc

# Directories
CFLAGS = -IheaderFiles -Wall -Wextra -std=c11
SRCDIR = sourceFiles

# Target executable
TARGET = game.exe

# Source files
SRCS = $(SRCDIR)/main.c $(SRCDIR)/Item.c $(SRCDIR)/Creature.c $(SRCDIR)/Player.c $(SRCDIR)/Room.c $(SRCDIR)/Game.c

# Object files
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Build target
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

# Clean generated files
clean:
	rm -f $(TARGET)

# Rebuild everything
rebuild: clean all