.PHONY: all test clean

BUILD_DIR := build

all:
	cmake -B $(BUILD_DIR)
	cd $(BUILD_DIR) && make

test: all
	cd $(BUILD_DIR) && ctest --output-on-failure

clean:
	-rm -rf $(BUILD_DIR)
