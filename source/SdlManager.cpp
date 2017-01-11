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

#include <stdint.h>

#include "SdlManager.hpp"
#include "Vec.hpp"

bool SdlManager::mustQuit = false;
std::vector<SdlManager::KeyChangeFunc> SdlManager::keyChangeFuncs;
std::vector<SdlManager::ResizeFunc> SdlManager::resizeFuncs;

SDL_Window *SdlManager::window = nullptr;
SDL_Renderer *SdlManager::renderer = nullptr;

void SdlManager::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		exit(1);

	window = SDL_CreateWindow("Sentempa",
							SDL_WINDOWPOS_CENTERED,
							SDL_WINDOWPOS_CENTERED,
							screenWidth, screenHeight,
							SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL |
							SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	if (!window || !renderer)
		exit(1);
}

void SdlManager::destroy()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

Vec2i SdlManager::getSize()
{
	int sx, sy;
	SDL_GetWindowSize(window, &sx, &sy);
	return
	{
		sx, sy
	};
}

SDL_Renderer *SdlManager::getSdlRenderer()
{
	return renderer;
}

void SdlManager::update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
		switch (event.type)
		{
		case SDL_QUIT:
			mustQuit = true;
			break;
		case SDL_KEYDOWN:
			for (auto &keyDownFunc : keyChangeFuncs)
				keyDownFunc(event.key.keysym.sym, true);
			break;
		case SDL_KEYUP:
			for (auto &keyDownFunc : keyChangeFuncs)
				keyDownFunc(event.key.keysym.sym, false);
			break;
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				for (auto &resizeFunc : resizeFuncs)
					resizeFunc(event.window.data1, event.window.data2);
			break;
		default:
			break;
		}
}

bool SdlManager::shouldQuit()
{
	return mustQuit;
}

void SdlManager::onKeyChange(const KeyChangeFunc func)
{
	keyChangeFuncs.push_back(func);
}

void SdlManager::onResize(const ResizeFunc func)
{
	resizeFuncs.push_back(func);
}
