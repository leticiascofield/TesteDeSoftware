# Compiler
CXX = g++

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Flags
CXXFLAGS = -std=c++11 -Wall -I$(INCLUDE_DIR)

# Targets
TARGET = main

$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Dependencies
$(BUILD_DIR)/Biblioteca.o: $(INCLUDE_DIR)/Biblioteca.hpp $(INCLUDE_DIR)/Livro.hpp
$(BUILD_DIR)/Livro.o: $(INCLUDE_DIR)/Livro.hpp

# Phony targets
.PHONY: clean

clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)
