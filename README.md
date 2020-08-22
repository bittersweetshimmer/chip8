# chip8
A [CHIP-8](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM) emulator.
* Sound not implemented.
* Runs at [500Hz](https://github.com/bittersweetshimmer/chip8/blob/master/chip8/src/main.cpp#L10).
* Quits if an invalid instruction is encountered.
* [`DRW`](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#Dxyn) wraps around the display.
* Ignores [`SYS`](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#0nnn).

### Build
```sh
> git submodule update --init --recursive # pull the dependencies
> mkdir build
> cd build
> cmake ..
> cmake --build . --target chip8 -j8
```

### Usage
Just drop any valid ROM on the window.

### 3rd party code
- [GLFW](https://www.glfw.org/) - OpenGL library - `zlib/libpng`
- [gloomy](https://github.com/bittersweetshimmer/gloomy) - My OpenGL reusable stuff - `MIT`