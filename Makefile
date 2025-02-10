# Define the compiler and flags
CXX = /opt/homebrew/opt/llvm/bin/clang++
CXXFLAGS = -fcolor-diagnostics -fansi-escape-codes -g -pedantic-errors -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -fopenmp -std=c++23 -O0 -arch arm64
INCLUDES = -Isrc -I/opt/homebrew/Cellar/SDL2/2.30.11/include -I/opt/homebrew/Cellar/glew/2.2.0_1/include -I/opt/homebrew/Cellar/glm/1.0.1/include
LDFLAGS = -L/opt/homebrew/Cellar/SDL2/2.30.11/lib -L/opt/homebrew/Cellar/glew/2.2.0_1/lib -L/opt/homebrew/Cellar/glm/1.0.1/lib
LINKER_FLAGS = -lsdl2 -framework OpenGL -lglew -lglm

# Directories
SRC_DIR = src
BUILD_DIR = build
LIB_DIR = lib
VENDOR_DIR = vendor

# Source files (recursive wildcard)
SRCS = $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(VENDOR_DIR)/**/*.cpp)
OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)
TARGET = $(LIB_DIR)/libopenglframework.a

# Target to build the framework static library
all: $(TARGET)

$(TARGET): $(OBJS)
	mkdir -p $(LIB_DIR)
	ar rcs $@ $^

$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(LIB_DIR)

.PHONY: all clean
