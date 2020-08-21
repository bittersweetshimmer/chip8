# chip8
A [`CHIP-8`](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM) emulator. Sound not implemented.

### Build
```sh
> git submodule update --init --recursive # pull the dependencies
> mkdir build
> cd build
> cmake ..
> make -j8 # or `msbuild chip8.sln /m` if you're using Visual Studio 
```

### Usage
Just drop any valid ROM on the window.

### 3rd party code
- [GLFW](https://www.glfw.org/) - OpenGL library - `zlib/libpng`
- [gloomy](https://github.com/bittersweetshimmer/gloomy) - My OpenGL reusable stuff - `MIT`