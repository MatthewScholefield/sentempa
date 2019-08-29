#include <SDL2/SDL_keyboard.h>
#include "InputManager.hpp"
#include "SdlManager.hpp"

InputManager::InputManager() :
        controls({{SDLK_LEFT,  Key::lookLeft},
                  {SDLK_RIGHT, Key::lookRight},
                  {SDLK_UP,    Key::lookUp},
                  {SDLK_DOWN,  Key::lookDown},

                  {SDLK_a,     Key::moveLeft},
                  {SDLK_d,     Key::moveRight},
                  {SDLK_w,     Key::moveUp},
                  {SDLK_s,     Key::moveDown},
                  {SDLK_e,     Key::moveForwards},
                  {SDLK_q,     Key::moveBackwards}}) {
    cauto incrementKey = [](Key &key) {
        key = (Key) ((cint) key + 1);
    };

    for (Key key = Key::begin; key != Key::end; incrementKey(key))
        keyPressed[key] = false;

    SdlManager::onKeyChange([this](const SDL_Keycode key, cbool keyDown) {
        onKeyDown(key, keyDown);
    });
}

bool InputManager::isKeyPressed(const Key key) const {
    auto result = keyPressed.find(key);
    if (result == keyPressed.end())
        throw std::logic_error("Key pressed entry not found!");
    return result->second;
}

void InputManager::onKeyDown(const SDL_Keycode key, cbool keyDown) {
    auto controlKeyIt = controls.find(key);
    if (controlKeyIt == controls.end())
        return;

    auto keyStateIt = keyPressed.find(controlKeyIt->second);
    if (keyStateIt == keyPressed.end())
        throw std::logic_error("Key pressed entry not found!");
    keyStateIt->second = keyDown;
}

void InputManager::update() {
    SDL_GetRelativeMouseState(&mouseDx, &mouseDy);
}

int InputManager::getMouseDx() const {
    return mouseDx;
}

int InputManager::getMouseDy() const {
    return mouseDy;
}

