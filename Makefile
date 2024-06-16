
BLD_DIR := build
SRC_DIR := Code
CXX := g++

TREE_DIRS := \
	build_board_config \
	validate_board_config \
	file_manager \
	board_config_field_parser \
	board_config_field_titles # TODO: figure out if this is nesccary 
TREE_DIRS := $(addprefix $(BLD_DIR)/, $(TREE_DIRS))

# Swap the debug definitions for non-debug builds
DEBUG := -g
#DEBUG :=

CXXFLAGS := -Wall -O2 $(DEBUG)

.PHONY: all clean

EXECUTABLES := \
	build_board_config.out \
	validate_board_config.out
EXECUTABLES := $(addprefix $(BLD_DIR)/, $(EXECUTABLES))

BUILD_BOARD_CONFIG_OBJS := \
	file_manager/file_manager.o \
	build_board_config/build_board_config.o \
	build_board_config/main.o
BUILD_BOARD_CONFIG_OBJS := $(addprefix $(BLD_DIR)/, $(BUILD_BOARD_CONFIG_OBJS))

VALIDATE_BOARD_CONFIG_OBJS := \
	file_manager/file_manager.o \
	validate_board_config/validate_board_config.o \
	validate_board_config/main.o \
	board_config_field_parser/board_config_field_parser.o
VALIDATE_BOARD_CONFIG_OBJS := $(addprefix $(BLD_DIR)/, $(VALIDATE_BOARD_CONFIG_OBJS))


all: $(EXECUTABLES)

clean:
	rm -rv $(BLD_DIR)

$(BLD_DIR):
	mkdir -p $(BLD_DIR)

$(TREE_DIRS):
	mkdir -p $(TREE_DIRS)

$(BLD_DIR)/build_board_config.out: $(BUILD_BOARD_CONFIG_OBJS) | $(BLD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(BUILD_BOARD_CONFIG_OBJS)

$(BLD_DIR)/validate_board_config.out: $(VALIDATE_BOARD_CONFIG_OBJS) | $(BLD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(VALIDATE_BOARD_CONFIG_OBJS)

$(BLD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(TREE_DIRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BLD_DIR)/%.o: $(SRC_DIR)/%.cpp  $(SRC_DIR)/%.h | $(TREE_DIRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@
