CXX := g++

EXECUTABLE ?= build/board_demo-simple

SRC_DIR ?= 
BLD_DIR ?= build
ASCII_ENGINE_DIR ?= ../../build
INC_DIR := $(shell find $(SRC_DIR) -type d)

SRCS := $(shell find $(SRC_DIR) -name *.cpp)
OBJS := $(SRCS:%=$(BLD_DIR)/%.o)
DEPS := $(OCJS:.o=.d)

LDFLAGS := -lncurses -L $(ASCII_ENGINE_DIR) -lascii_engine
INC_FLAGS := $(addprefix -I,$(INC_DIR))
CXXFLAGS := -std=c++17 $(LDFLAGS) -O2 $(INC_FLAGS) -Wall -MMD -MP -I $(ASCII_ENGINE_DIR)/headers/ascii_engine

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(BLD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	cp -r board_configs/ build/

clean:
	-rm -r $(BLD_DIR)

-include $(DEPS)
