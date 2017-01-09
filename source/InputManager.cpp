/*
 * Copyright (C) 2017 Matthew D. Scholefield
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <SDL2/SDL_keyboard.h>
#include "InputManager.hpp"
#include "SdlManager.hpp"

InputManager::InputManager() :
controls({
	{SDLK_LEFT, Key::lookLeft},
	{SDLK_RIGHT, Key::lookRight},
	{SDLK_UP, Key::lookUp},
	{SDLK_DOWN, Key::lookDown},

	{SDLK_a, Key::moveLeft},
	{SDLK_d, Key::moveRight},
	{SDLK_w, Key::moveUp},
	{SDLK_s, Key::moveDown},
	{SDLK_e, Key::moveForwards},
	{SDLK_q, Key::moveBackwards},
})
{
	auto incrementKey = [](Key & key)
	{
		key = (Key) ((int) key + 1);
	};

	for (Key key = Key::begin; key != Key::end; incrementKey(key))
		keyPressed[key] = false;

	SdlManager::onKeyChange([this](SDL_Keycode key, bool keyDown)
	{
		onKeyDown(key, keyDown);
	});
}

bool InputManager::isKeyPressed(const Key key) const
{
	auto result = keyPressed.find(key);
	if (result == keyPressed.end())
		throw std::logic_error("Key pressed entry not found!");
	return result->second;
}

void InputManager::onKeyDown(SDL_Keycode key, bool keyDown)
{
	auto controlKeyIt = controls.find(key);
	if (controlKeyIt == controls.end())
		return;

	auto keyStateIt = keyPressed.find(controlKeyIt->second);
	if (keyStateIt == keyPressed.end())
		throw std::logic_error("Key pressed entry not found!");
	keyStateIt->second = keyDown;
}

void InputManager::update()
{
	SDL_GetRelativeMouseState(&mouseDx, &mouseDy);
}

int InputManager::getMouseDx() const
{
	return mouseDx;
}

int InputManager::getMouseDy() const
{
	return mouseDy;
}

