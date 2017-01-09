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

#pragma once

#include <unordered_map>
#include <SDL2/SDL_keycode.h>

enum class Key
{
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

class InputManager
{
public:
	InputManager();

	void onKeyDown(SDL_Keycode key, bool keyDown);
	bool isKeyPressed(const Key key) const;
	void update();
	int getMouseDx() const;
	int getMouseDy() const;

private:
	std::unordered_map<SDL_Keycode, Key> controls;
	std::unordered_map<Key, bool> keyPressed;
	int mouseDx = 0, mouseDy = 0;
};
