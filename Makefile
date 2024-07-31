# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -g -Iinclude
LIBS = -lSDL2 -lSDL2_ttf

# Directories
SRCDIR = src
BINDIR = bin
OBJDIR = obj

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
# Object files
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Executable
TARGET = $(BINDIR)/main

# Default target
all: $(TARGET) run

# Rule to build the target
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(LIBS) -o $@ $(OBJECTS)

# Rule to compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(LIBS) -c $< -o $@

run:
	./bin/main

# Clean up build artifacts
clean:
	rm -rf $(BINDIR) $(OBJDIR)

# Rebuild everything
rebuild: clean all

.PHONY: all clean rebuild
