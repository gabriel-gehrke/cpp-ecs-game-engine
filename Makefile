# compiler arguments
CPP_ARGS := -std=c++17 -Wall -g -O3 -march=native -ffast-math

# configure important directories
BUILD_DIR := ./build
SRC_DIR := ./src

# make dependency lists
CPP_FILES := $(shell find $(SRC_DIR) -name *.cpp)
OBJ_FILES := $(subst .cpp,.o,$(subst $(SRC_DIR),$(BUILD_DIR),$(CPP_FILES)))

# debugging deps
#$(info CPP_FILES is $(CPP_FILES))
#$(info OBJ_FILES is $(OBJ_FILES))

build/executable: build/resources.cpp $(OBJ_FILES)
	@mkdir -p $(@D)
	g++ $(CPP_ARGS) -o $@ build/resources.cpp $(OBJ_FILES) -lSDL2 -lSDL2_image -lSDL2_ttf -Iinclude

build/resources.cpp:
	@mkdir -p $(@D)
	python3 scripts/make-resources.py

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	g++ $(CPP_ARGS) -c $< -o $@ -Iinclude	

clean:
	rm -rf ./build/
	mkdir -p ./build