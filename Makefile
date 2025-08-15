CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LIBS = -lSDL2

SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TARGET = $(BINDIR)/sorting_visualizer

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(OBJECTS) -o $(TARGET) $(LIBS)
	@echo "Built $@"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

.PHONY: clean run

clean:
	rm -rf $(OBJDIR) $(BINDIR)

run: $(TARGET)
	$(TARGET)

debug: CFLAGS += -g
debug: $(TARGET)
	@echo "Built with debug info"
