SOURCE:=$(shell find ./src -name *.cpp)

build/main:
	mkdir -p ./build
	g++ -std=c++11 -O3 -ftree-vectorize -march=native -ffast-math -o build/main $(SOURCE) -lSDL2 -Iinclude
clean:
	rm -rf ./build/