# Define the C++ compiler and compile flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall

# Define the source, object, and executable directories for the compiler
COMPILER_SRC_DIR = src/compiler
COMPILER_OBJ_DIR = obj/compiler
COMPILER_BIN_DIR = bin

# Define the source, object, and executable directories for the interpreter
INTERPRETER_SRC_DIR = src/interpreter
INTERPRETER_OBJ_DIR = obj/interpreter
INTERPRETER_BIN_DIR = bin

# Find all source files recursively in COMPILER_SRC_DIR and INTERPRETER_SRC_DIR
COMPILER_SRCS = $(shell find $(COMPILER_SRC_DIR) -type f -name '*.cpp')
INTERPRETER_SRCS = $(shell find $(INTERPRETER_SRC_DIR) -type f -name '*.cpp')

# Create object file paths from source files for the compiler
COMPILER_OBJS = $(patsubst $(COMPILER_SRC_DIR)/%.cpp, $(COMPILER_OBJ_DIR)/%.o, $(COMPILER_SRCS))

# Create object file paths from source files for the interpreter
INTERPRETER_OBJS = $(patsubst $(INTERPRETER_SRC_DIR)/%.cpp, $(INTERPRETER_OBJ_DIR)/%.o, $(INTERPRETER_SRCS))

# The name of the final executables
COMPILER_TARGET = $(COMPILER_BIN_DIR)/compiler
INTERPRETER_TARGET = $(INTERPRETER_BIN_DIR)/interpreter

# Default make targets (build both executables)
all: $(COMPILER_TARGET) $(INTERPRETER_TARGET)

compiler: $(COMPILER_TARGET)

interpreter: $(INTERPRETER_TARGET)

# Rule to link the compiler executable from object files
$(COMPILER_TARGET): $(COMPILER_OBJS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to link the interpreter executable from object files
$(INTERPRETER_TARGET): $(INTERPRETER_OBJS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to compile source files into object files for the compiler
$(COMPILER_OBJ_DIR)/%.o: $(COMPILER_SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to compile source files into object files for the interpreter
$(INTERPRETER_OBJ_DIR)/%.o: $(INTERPRETER_SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean the generated files for both compiler and interpreter
clean:
	rm -rf $(COMPILER_OBJ_DIR) $(INTERPRETER_OBJ_DIR) $(COMPILER_BIN_DIR) $(INTERPRETER_BIN_DIR)

.PHONY: all clean
