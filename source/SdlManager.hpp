#pragma once

#include <vector>
#include <functional>
#include <SDL2/SDL.h>
#include "Vec.hpp"
#include "types.hpp"

class SdlManager {
public:
    SdlManager() = delete;
    using KeyChangeFunc = std::function<void(const SDL_Keycode, cbool keyDown)>;
    using ResizeFunc = std::function<void(cint, cint)>;

    static void init();
    static void destroy();
    static Vec2i getSize();
    static SDL_Renderer *getSdlRenderer();
    static void update();
    static bool shouldQuit();
    static void onKeyChange(KeyChangeFunc func);
    static void onResize(ResizeFunc func);

private:
    static cint screenWidth = 640;
    static cint screenHeight = 480;

    static bool mustQuit;
    static std::vector<KeyChangeFunc> keyChangeFuncs;
    static std::vector<ResizeFunc> resizeFuncs;

    static SDL_Window *window;
    static SDL_Renderer *renderer;
};
