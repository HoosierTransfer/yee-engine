CC := gcc
CXX := g++
CFLAGS := -std=c11 -Werror -g -Iinclude
CXXFLAGS := -std=c++17 -Werror -g -Iinclude
LDFLAGS := -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
BIN_DIR := bin
SRC_DIR := src
OBJ_DIR := obj
INCLUDE_DIR := include

CPP_SRC := $(shell find $(SRC_DIR) -name '*.cpp')
C_SRC := $(shell find $(SRC_DIR) -name '*.c')

CPP_OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CPP_SRC))
C_OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRC))
OBJ := $(CPP_OBJ) $(C_OBJ)

TARGET := main

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean