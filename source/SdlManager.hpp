/*
 * Copyright (C) 2016 Matthew D. Scholefield
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

#include <vector>
#include <functional>
#include <SDL2/SDL.h>
#include "Vec.hpp"

class SdlManager
{
	SdlManager() = delete;
public:
	using KeyDownFunc = std::function<void(SDL_Keycode)>;
	using ResizeFunc = std::function<void(int, int) >;

	static void init();
	static void destroy();
	static Vec2i getSize();
	static SDL_Renderer *getSdlRenderer();
	static void update();
	static bool shouldQuit();
	static void onKeyDown(KeyDownFunc func);
	static void onResize(ResizeFunc func);

private:
	static const int screenWidth = 640;
	static const int screenHeight = 480;

	static bool mustQuit;
	static std::vector<KeyDownFunc> keyDownFuncs;
	static std::vector<ResizeFunc> resizeFuncs;

	static SDL_Window *window;
	static SDL_Renderer *renderer;
};
