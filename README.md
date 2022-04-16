# cpp-ecs-game-engine

### Features
- [x] Entities
- [x] Components
- [x] Collisions
- [x] FPS-independent physics
- [x] Drawing simple shapes
- [x] Sprites
- [x] Keyboard input
- [ ] Mouse input
- [ ] Controller input
- [ ] Particle systems
- [ ] File IO / Serialization
- [ ] Event System
- [ ] UI / Text
- [ ] Shaders
- [ ] Sound


### Requirements
Before compiling the engine/game, make sure that the following libraries/programs are installed on the system:
```
g++ (or equivalent c++ compiler)
make
cmake
libsdl2-dev
libsdl2-image-dev
```
e.g.: (on Ubuntu 20 / Debian 11)
```
sudo apt update && sudo apt install g++ make cmake python3 libsdl2-dev libsdl2-image-dev
```

Note: the actual package names may differ for your distro and package manager.

### Getting started

To build the project switch into the build/ directory and run
```
cmake ..
```
to let CMake build the MakeFile for the project. Afterwards run
```
make 
```
to build the project. Add the -j option to allow make to run multiple jobs at once.<br>
After the build process finished you find the...
* executable in the build/app/ directory
* produced engine library in the build/src/ directory
* produced test executable in the build/test/ directory 

### Possible Problems

CMake might have a Problem finding the SDL2_image lib on your System if you are on a x64 Linux System.<br>
In that case CMake won't build the MakeFile and stop when running ```cmake ..```. <br>
If that's the case do the following:

* Go to /usr/lib/x86_64-linux-gnu/cmake 
* Create a directory called "sdl2_image"
* Switch into the directory
* Create a file called sdl2_image-config.cmake (This will later be our SDL2_image cmake configuration file)
* Put the following into the file:
```
set(prefix "/usr")
set(exec_prefix "${prefix}")
set(libdir "${prefix}/lib/x86_64-linux-gnu")
set(SDL2_IMAGE_PREFIX "/usr")
set(SDL2_IMAGE_EXEC_PREFIX "/usr")
set(SDL2_IMAGE_INCLUDE_DIRS "${prefix}/include/SDL2_image")
set(SDL2_IMAGE_LIBRARIES "-lSDL2_image")
```
Now CMake should be able to find the Library and should be able to create the MakeFile.