#pragma once

#include <unordered_map>
#include <SDL2/SDL_keycode.h>
#include "types.hpp"

enum class Key {
    begin = 0,

    lookLeft = Key::begin,
    lookRight,
    lookUp,
    lookDown,

    moveLeft,
    moveRight,
    moveUp,
    moveDown,
    moveForwards,
    moveBackwards,

    size,
    end = Key::size
};

class InputManager {
public:
    InputManager();

    void onKeyDown(const SDL_Keycode key, cbool keyDown);
    bool isKeyPressed(const Key key) const;
    void update();
    int getMouseDx() const;
    int getMouseDy() const;

private:
    std::unordered_map<SDL_Keycode, Key> controls;
    std::unordered_map<Key, bool> keyPressed;
    int mouseDx = 0, mouseDy = 0;
};
