# Sentempa
Sentempa is a unique 3D space game in that the rendering is has been coded from scratch (using SDL2). As a result, in part due to the simplicity of the game, the preformance is silky smooth.

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
Sentempa depends on SDL2 and, by default, is compiled using clang. In Ubuntu you can install these with `sudo apt-get install libsdl2-dev clang-3.5`.

### Compiling
Simply run `make` and it will compile everything. 

### Running
The executable should be created in a subdirectory in the `dist` folder. To run it type `./dist/` followed by the full path of the binary. For me the command would be `./dist/Debug/CLang-Linux/sentempa`.

# Development
This project uses Netbeans IDE and as a result, can simply be imported to get things up and running quickly. A breif note about the source: constant types are often aliased to just a letter `c` in front of the name. For instance, `const int` is simply called `cint`. This is to promote the use of `const` without requiring much extra typing while maintaining realatively good readability.

# Contact
Contact me either at `matthew3311999@gmail.com` or by filing an issue on GitHub.

[screenshot]:https://i.imgbox.com/f3zUlU2a.gif
[video]:https://goo.gl/photos/buxJtu8aByhBFx2z6

