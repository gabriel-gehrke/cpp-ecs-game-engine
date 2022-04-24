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
libsdl2-ttf-dev
```
e.g.: (on Ubuntu 20 / Debian 11)
```
sudo apt update && sudo apt install g++ make cmake python3 libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
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

