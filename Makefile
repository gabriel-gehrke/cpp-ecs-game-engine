# configure importand directories
BUILD_DIR := ./build
SRC_DIR := ./src
RES_DIR := ./resources

RES_FILE := build/resources.cpp

# make dependency lists
CPP_FILES := $(shell find $(SRC_DIR) -name *.cpp)
RES_FILES := $(shell find $(RES_DIR))
OBJ_FILES := $(subst .cpp,.o,$(subst $(SRC_DIR),$(BUILD_DIR),$(CPP_FILES)))

# debugging deps
#$(info CPP_FILES is $(CPP_FILES))
#$(info OBJ_FILES is $(OBJ_FILES))

CPP_ARGS := -std=c++17 -O3 -ftree-vectorize -march=native -ffast-math -lstdc++


build/engine: $(OBJ_FILES)
	@mkdir -p $(@D)
	python3 ./make-resources.py
	g++ $(CPP_ARGS) -o $@ $(OBJ_FILES) $(RES_FILE) -lSDL2 -Iinclude

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	g++ $(CPP_ARGS) -c $< -o $@ -Iinclude	

clean:
	rm -rf ./build/
