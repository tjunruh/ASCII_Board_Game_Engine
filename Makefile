
BLD_DIR := build
SRC_DIR := Code
CXX := g++

TREE_DIRS := \
	$(BLD_DIR) \
	build_board_config \
	validate_board_config \
	file_manager \
	board_config_field_parser \
	ascii_engine \
	headers/ascii_engine \
	test_ascii_engine \
	board_config_field_titles
TREE_DIRS := $(addprefix $(BLD_DIR)/, $(TREE_DIRS))

# Swap the debug definitions for debug builds
#DEBUG := -g
DEBUG :=

LIBS := -lncurses
CXXFLAGS := -Wall -O2 $(DEBUG) -Iexternal_libraries -MMD

TEST_ASCII_ENGINE := test_ascii_engine.out

EXECUTABLES := \
	build_board_config.out \
	validate_board_config.out \
	$(TEST_ASCII_ENGINE)
EXECUTABLES := $(addprefix $(BLD_DIR)/, $(EXECUTABLES))

.PHONY: all clean engine test test-headless

all: $(EXECUTABLES) engine

clean:
	-rm -rf $(BLD_DIR)

$(TREE_DIRS):
	mkdir -p $@

ALL_OBJS :=

### ASCII Engine
ASCII_ENGINE_HEADERS_DIR := $(BLD_DIR)/headers/ascii_engine

ASCII_ENGINE_LIBRARY := libascii_engine.so
ASCII_LIB := -L$(BLD_DIR) -lascii_engine
ASCII_INCLUDE := -I$(BLD_DIR)/headers

ASCII_ENGINE_OBJS := \
	ascii_board.o \
	ascii_io.o \
	dec_formatter.o \
	format_tools.o \
	controls.o \
	frame.o \
	label.o \
	logger.o \
	menu.o \
	text_box.o \
	widget.o
ASCII_ENGINE_OBJS := $(addprefix $(BLD_DIR)/ascii_engine/, $(ASCII_ENGINE_OBJS))
ALL_OJBS += $(ASCII_ENGINE_OBJS)

ASCII_ENGINE_OBJS_EXTERNAL := \
	board_config_field_parser/board_config_field_parser.o \
	validate_board_config/validate_board_config.o \
	file_manager/file_manager.o
ASCII_ENGINE_OBJS_EXTERNAL := $(addprefix $(BLD_DIR)/, $(ASCII_ENGINE_OBJS_EXTERNAL))
ALL_OBJS += $(ASCII_ENGINE_OBJS_EXTERNAL)

ASCII_ENGINE_HEADERS := \
	ascii_board.h \
	ascii_io.h \
	controls.h \
	error_codes.h \
	dec_formatter.h \
	file_manager.h \
	format_tools.h \
	frame.h \
	label.h \
	logger.h \
	menu.h \
	text_box.h \
	widget.h \
	widget_types.h
ASCII_ENGINE_HEADERS := $(addprefix $(BLD_DIR)/headers/ascii_engine/, $(ASCII_ENGINE_HEADERS))

$(BLD_DIR)/headers/ascii_engine/%.h: $(SRC_DIR)/ascii_engine/%.h | $(ASCII_ENGINE_HEADERS_DIR)
	cp $< $@

$(BLD_DIR)/headers/ascii_engine/%.h: $(SRC_DIR)/file_manager/%.h | $(ASCII_ENGINE_HEADERS_DIR)
	cp $< $@

$(BLD_DIR)/ascii_engine/%.o: $(SRC_DIR)/ascii_engine/%.cpp | $(addprefix $(BLD_DIR)/, ascii_engine)
	$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@

$(BLD_DIR)/$(ASCII_ENGINE_LIBRARY): $(ASCII_ENGINE_OBJS) $(ASCII_ENGINE_OBJS_EXTERNAL)
	$(CXX) $(CXXFLAGS) -shared -o $@ $(ASCII_ENGINE_OBJS) $(ASCII_ENGINE_OBJS_EXTERNAL) $(LIBS)
### End ASCII Engine

### ASCII Engine Test
TEST_ASCII_ENGINE_OBJS := \
	main.o \
        ascii_board.o \
	ascii_io.o \
	controls.o \
	format_tools.o \
        frame.o \
        label.o \
        menu.o \
        widget.o
TEST_ASCII_ENGINE_OBJS := $(addprefix $(BLD_DIR)/test_ascii_engine/, $(TEST_ASCII_ENGINE_OBJS))
ALL_OBJS += $(TEST_ASCII_ENGINE_OBJS)

$(BLD_DIR)/test_ascii_engine/%.o: $(SRC_DIR)/test_ascii_engine/%.cpp $(ASCII_ENGINE_HEADERS) | $(BLD_DIR)/test_ascii_engine
	$(CXX) $(CXXFLAGS) $(ASCII_INCLUDE) -c $< -o $@

$(BLD_DIR)/test_ascii_engine.out: $(TEST_ASCII_ENGINE_OBJS) $(BLD_DIR)/$(ASCII_ENGINE_LIBRARY) $(ASCII_ENGINE_OBJS_EXTERNAL) | $(BLD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_ASCII_ENGINE_OBJS) $(ASCII_ENGINE_OBJS_EXTERNAL) $(ASCII_LIB) $(LIBS) -pthread -lgtest
### End ASCII Engine Test



### File manager
FILE_MANAGER_OBJS := \
	file_manager.o
FILE_MANAGER_OBJS := $(addprefix $(BLD_DIR)/file_manager/, $(FILE_MANAGER_OBJS))
ALL_OBJS += $(FILE_MANAGER_OBJS)

$(BLD_DIR)/file_manager/%.o: $(SRC_DIR)/file_manager/%.cpp | $(BLD_DIR)/file_manager
	$(CXX) -c $< -o $@
### End file manager


### Board config field parser
BOARD_CONFIG_FIELD_PARSER_OBJS := \
	board_config_field_parser.o
BOARD_CONFIG_FIELD_PARSER_OBJS := $(addprefix $(BLD_DIR)/board_config_field_parser/, $(BOARD_CONFIG_FIELD_PARSER_OBJS))
ALL_OBJS += $(BOARD_CONFIG_FIELD_PARSER_OBJS)

$(BLD_DIR)/board_config_field_parser/%.o: $(SRC_DIR)/board_config_field_parser/%.cpp | $(BLD_DIR)/board_config_field_parser
	$(CXX) $(CXXFLAGS) -c $< -o $@
### End board config field parser



### Build board config
BUILD_BOARD_CONFIG_OBJS := \
	build_board_config.o \
	main.o
BUILD_BOARD_CONFIG_OBJS := $(addprefix $(BLD_DIR)/build_board_config/, $(BUILD_BOARD_CONFIG_OBJS))
ALL_OBJS += $(BUILD_BOARD_CONFIG_OBJS)

$(BLD_DIR)/build_board_config/%.o: $(SRC_DIR)/build_board_config/%.cpp | $(BLD_DIR)/build_board_config
	$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@

$(BLD_DIR)/build_board_config.out: $(BUILD_BOARD_CONFIG_OBJS) $(FILE_MANAGER_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(BUILD_BOARD_CONFIG_OBJS) $(FILE_MANAGER_OBJS)
### End build board config 


### Validate board config
VALIDATE_BOARD_CONFIG_OBJS := \
	validate_board_config.o \
	main.o
VALIDATE_BOARD_CONFIG_OBJS := $(addprefix $(BLD_DIR)/validate_board_config/, $(VALIDATE_BOARD_CONFIG_OBJS))
ALL_OBJS += $(VALIDATE_BOARD_CONFIG_OBJS)

$(BLD_DIR)/validate_board_config/%.o: $(SRC_DIR)/validate_board_config/%.cpp | $(BLD_DIR)/validate_board_config
	$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@

$(BLD_DIR)/validate_board_config.out: $(VALIDATE_BOARD_CONFIG_OBJS) $(FILE_MANAGER_OBJS) $(BOARD_CONFIG_FIELD_PARSER_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(VALIDATE_BOARD_CONFIG_OBJS) $(FILE_MANAGER_OBJS) $(BOARD_CONFIG_FIELD_PARSER_OBJS)
### End validate board config


### PHONY targets requiring other variables
test: $(BLD_DIR)/$(TEST_ASCII_ENGINE)
	env LD_LIBRARY_PATH="./$(BLD_DIR)" $<

test-headless: $(BLD_DIR)/$(TEST_ASCII_ENGINE)
	env LD_LIBRARY_PATH="./$(BLD_DIR)" $< --gtest_filter=-ascii_io.*

engine: $(ASCII_ENGINE_HEADERS) $(addprefix $(BLD_DIR)/, $(ASCII_ENGINE_LIBRARY))
### End PHONY targets


# gcc option -MMD makes it output additional files that end with .d (as opposed to .o)
# which is a makefile with the user header files that it includes.
# To get all these makefiles we change the .o to a .d;
# that is why we add all objects to ALL_OBJS
DEPS := $(ALL_OBJS:.o=.d)

# Include dependencies but they might not be generated
# so we include ignoring if they do not exist
-include $(DEPS)
