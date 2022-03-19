SOURCE:=$(shell find ./src -name *.cpp)

build/main:
	mkdir -p ./build
	g++ -std=c++11 -O3 -o build/main $(SOURCE) `sdl2-config --cflags --libs` -Iinclude
clean:
	rm -rf ./build/