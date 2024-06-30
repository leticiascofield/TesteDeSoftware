# Variables
CXX = g++
CXXFLAGS = -Iinclude -Wall -Wextra -std=c++17 -fprofile-arcs -ftest-coverage
LDFLAGS =

# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

# Source Files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
SRC_FILES_NO_TESTS = $(filter-out $(SRC_DIR)/tests.cpp, $(SRC_FILES))
SRC_FILES_ONLY_TESTS = $(filter-out $(SRC_DIR)/main.cpp, $(SRC_FILES))

# Object Files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))
OBJ_FILES_NO_TESTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES_NO_TESTS))
OBJ_FILES_ONLY_TESTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES_ONLY_TESTS))

# Targets
TARGET_RUN = main
TARGET_TEST = tests

# Default Target
all: $(TARGET_RUN) $(TARGET_TEST)

# Run Target
run: $(TARGET_RUN)
	@./$(TARGET_RUN)

$(TARGET_RUN): $(OBJ_FILES_NO_TESTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Test Target
test: $(TARGET_TEST)
	@./$(TARGET_TEST)

$(TARGET_TEST): $(OBJ_FILES_ONLY_TESTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Build Object Files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean Target
clean:
	$(RM) $(BUILD_DIR)/*.o $(TARGET_RUN) $(TARGET_TEST)

.PHONY: all run test clean
