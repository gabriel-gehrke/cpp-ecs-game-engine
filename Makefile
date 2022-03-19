build/main:
	mkdir -p ./build
	g++ -O3 -o build/main src/* `sdl2-config --cflags --libs` -Iinclude
clean:
	rm -rf ./build/