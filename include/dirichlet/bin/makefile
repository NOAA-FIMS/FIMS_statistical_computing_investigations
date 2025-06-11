# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -w -O2 -std=c++11
# Target executable
TARGET = dirichlet
# Source file (in parent directory)
SRC = ../dirichlet.cpp
# Object file
OBJ = dirichlet.o

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Rule to compile source into object file
$(OBJ): $(SRC)
	$(CXX) $(CXXFLAGS) -c $(SRC) -o $(OBJ)

# Clean rule to remove build artifacts
clean:
	rm -f $(TARGET) $(OBJ)
	rm -f *.csv
	rm -f *.txt
