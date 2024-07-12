
BLD_DIR := build
SRC_DIR := Code
CXX := g++

TREE_DIRS := \
	build_board_config \
	validate_board_config \
	file_manager \
	board_config_field_parser \
	ascii_engine \
	headers/ascii_engine \
	test_ascii_engine \
	board_config_field_titles # TODO: figure out if this is nesccary 
TREE_DIRS := $(addprefix $(BLD_DIR)/, $(TREE_DIRS))

# Swap the debug definitions for non-debug builds
DEBUG := -g
#DEBUG :=

LIBS := -lncurses

CXXFLAGS := -Wall -O2 $(DEBUG) -fPIC -Iexternal_libraries

.PHONY: all clean engine

EXECUTABLES := \
	build_board_config.out \
	validate_board_config.out \
	test_ascii_engine.out
EXECUTABLES := $(addprefix $(BLD_DIR)/, $(EXECUTABLES))

ASCII_ENGINE_LIBRARY := libascii_engine.so

LIBRARIES := \
	$(ASCII_ENGINE_LIBRARY)
LIBRARIES := $(addprefix $(BLD_DIR)/, $(LIBRARIES))

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

ASCII_ENGINE_OBJS := \
	ascii_board.o \
	ascii_io.o \
	format_tools.o \
	controls.o \
	frame.o \
	menu.o \
	text_box.o \
	widget.o
ASCII_ENGINE_OBJS := $(addprefix $(BLD_DIR)/ascii_engine/, $(ASCII_ENGINE_OBJS))

ASCII_ENGINE_OBJS_EXTERNAL := \
	board_config_field_parser/board_config_field_parser.o \
	validate_board_config/validate_board_config.o \
	file_manager/file_manager.o
ASCII_ENGINE_OBJS_EXTERNAL := $(addprefix $(BLD_DIR)/, $(ASCII_ENGINE_OBJS_EXTERNAL))

TEST_ASCII_ENGINE := test_ascii_engine.out
TEST_ASCII_ENGINE_OBJS := \
	main.o
TEST_ASCII_ENGINE_OBJS := $(addprefix $(BLD_DIR)/test_ascii_engine/, $(TEST_ASCII_ENGINE_OBJS))

INCLUDE_ASCII_ENGINE_HEADERS := -I$(BLD_DIR)/headers
INCLUDE_ASCII_ENGINE := $(INCLUDE_ASCII_ENGINE_HEADERS) -L$(BLD_DIR) -lascii_engine

all: $(EXECUTABLES) $(LIBRARIES)

engine: $(LIBRARIES)

clean:
	-rm -rv $(BLD_DIR)

$(BLD_DIR):
	mkdir -p $(BLD_DIR)

$(TREE_DIRS):
	mkdir -p $(TREE_DIRS)

$(BLD_DIR)/$(TEST_ASCII_ENGINE): $(TEST_ASCII_ENGINE_OBJS) $(BLD_DIR)/$(ASCII_ENGINE_LIBRARY) | $(TREE_DIRS)
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_ASCII_ENGINE_OBJS) $(INCLUDE_ASCII_ENGINE)

$(BLD_DIR)/test_ascii_engine/%.o: $(SRC_DIR)/test_ascii_engine/%.cpp | $(TREE_DIRS)
	$(CXX) $(CXXFLAGS) $(INCLUDE_ASCII_ENGINE_HEADERS) -c $< -o $@

$(BLD_DIR)/$(ASCII_ENGINE_LIBRARY): $(ASCII_ENGINE_OBJS) $(ASCII_ENGINE_OBJS_EXTERNAL)
	$(CXX) $(CXXFLAGS) -shared -o $@ $(ASCII_ENGINE_OBJS) $(ASCII_ENGINE_OBJS_EXTERNAL) $(LIBS)

$(BLD_DIR)/build_board_config.out: $(BUILD_BOARD_CONFIG_OBJS) | $(BLD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(BUILD_BOARD_CONFIG_OBJS)

$(BLD_DIR)/validate_board_config.out: $(VALIDATE_BOARD_CONFIG_OBJS) | $(BLD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(VALIDATE_BOARD_CONFIG_OBJS)

$(BLD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(TREE_DIRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BLD_DIR)/%.o: $(SRC_DIR)/%.cpp  $(SRC_DIR)/%.h | $(TREE_DIRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@
