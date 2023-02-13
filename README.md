# Indie-Studio

This project was **group c++ project** aiming to implement a **crossplatform 3D bomberman** utilizing local multiplayer (same machine). It was built over a period of a month using [raylib](https://github.com/raysan5/raylib) as graphical library.

## Features

- **Crossplatform** (linux / windows)
- **Up to 4** local players
- **3D Animation**
- Raylib c++ encapsulation
- Procedurally generated maps
- Solo **AI mode**
- Game state saving
- Gameplay powerups

## Building

**This project supports cross platform building with windows.**

Make sure you have the following installed before attempting to build :

- Raylib
- Make
- CMake

For this project, we use cmake to generate a makefile that we can then use to build the main binary.

```
cmake CMakeLists.txt
make
```

The main binary is named ```bomberman.```