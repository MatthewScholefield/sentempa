# Sentempa
Sentempa is a unique 3D space game in that the rendering is has been coded from scratch (using SDL2). As a result, in part due to the simplicity of the game, the performance is silky smooth.

[![screenshot]][video]

# Progress
 - [x] 3D Point Rendering System
 - [x] Keyboard and Mouse Navigation
 - [x] Customizable Controls
 - [ ] Game Elements
 - [ ] Sounds
 - [ ] UI
 
# Installing

### Setup

To build Sentempa you need SDL2 and cmake. In Ubuntu you can install these
with `sudo apt-get install -y libsdl2-dev cmake`.

### Compiling

Compile like a standard CMake application:

```bash
mkdir build && cd build
cmake ..
make -j4
```

Run with:

```bash
./sentempa
```

# Development

Note about the source: constant types are often aliased to just a letter
`c` in front of the name. For instance, `const int` is simply called `cint`.
This is to promote the use of `const` without requiring much extra typing
while maintaining relatively good readability.

# Contact

Contact me either at `matthew3311999@gmail.com` or by filing an issue on GitHub.

[screenshot]:https://i.imgbox.com/f3zUlU2a.gif
[video]:https://goo.gl/photos/buxJtu8aByhBFx2z6

