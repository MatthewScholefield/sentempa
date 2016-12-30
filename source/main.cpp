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

#include "Camera.hpp"
#include "SdlManager.hpp"
#include "Renderer.hpp"
#include "Utility.hpp"
#include "StarField.hpp"

int main()
{
	SdlManager::init();
	
	Renderer renderer(SdlManager::getSdlRenderer(), SdlManager::getSize());
	Camera camera(renderer.getSize());
	auto whenResize = [&](int sx, int sy)
	{
		renderer.resize(sx, sy);
		camera.resize(sx, sy);
	};
	SdlManager::onResize(whenResize);
	auto onKeyDown = [&](SDL_Keycode key, bool keyDown)
	{
		const float speed = keyDown? 100.f : 0.f;
		switch(key)
		{
		case SDLK_w:
			camera.vel.y = -speed;
			break;
		case SDLK_s:
			camera.vel.y = speed;
			break;
		case SDLK_d:
			camera.vel.x = speed;
			break;
		case SDLK_a:
			camera.vel.x = -speed;
			break;
		case SDLK_UP:
			camera.vel.z = speed;
			break;
		case SDLK_DOWN:
			camera.vel.z = -speed;
			break;
		default:
			break;
		}
	};
	SdlManager::onKeyChange(onKeyDown);

	StarField starField;
	Utility::startTimer();

	while (!SdlManager::shouldQuit())
	{
		float dt = Utility::restartTimer();
		SdlManager::update();
		starField.update(dt, SdlManager::getSize(), camera);
		camera.update(dt);

		renderer.clear(0, 0, 0);
		{
			starField.render(renderer, camera);
		}
		renderer.draw();
		Utility::sleep(1);
	}

	SdlManager::destroy();
	return 0;
}
