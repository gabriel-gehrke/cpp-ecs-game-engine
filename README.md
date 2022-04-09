# cpp-ecs-game-engine

### Requirements
Before compiling the engine/game, make sure that the following libraries/programs are installed on the system:
```
g++ (or equivalent c++ compiler)
make
python3
libsdl2-dev
libsdl2-image-dev
```
e.g.: (on Ubuntu 20)
```
sudo apt update && sudo apt install g++ make python3 libsdl2-dev libsdl2-image-dev
```

Note: the actual package names my differ for your distro and package manager.

### Getting started

To compile the engine/game, simply run the `make` command.<br>
It can be parameterized to compile parts of the engine in parallel. e.g.: `make -j8` (8 threads)

### Features
- [x] Entities
- [x] Components
- [x] Kollisionen: Konvex & Konkav
- [x] Linien/Kreise/Punkte zeichnen
- [ ] Sprites
- [ ] Sound
