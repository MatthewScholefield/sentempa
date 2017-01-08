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

void updateMouse(Camera &camera)
{
	int dMouseX, dMouseY;
	SDL_GetRelativeMouseState(&dMouseX, &dMouseY);
	auto &ang = camera.getAngVel();
	ang.x = +0.3f * dMouseX;
	ang.y = -0.3f * dMouseY;
}

int main()
{
	SdlManager::init();

	Renderer renderer(SdlManager::getSdlRenderer(), SdlManager::getSize());
	Camera camera(renderer.getSize());
	StarField starField;

	Vec2f keyAng;
	auto onKeyDown = [&](SDL_Keycode key, bool keyDown)
	{
		auto &acc = camera.getAcc();
		const float setAcc = keyDown ? 200.f : 0.f;
		const float setAng = keyDown ? pi() / 2.f : 0.f;
		switch (key)
		{
		case SDLK_w:
			acc.y = -setAcc;
			break;
		case SDLK_s:
			acc.y = setAcc;
			break;
		case SDLK_d:
			acc.x = setAcc;
			break;
		case SDLK_a:
			acc.x = -setAcc;
			break;
		case SDLK_e:
			acc.z = setAcc;
			break;
		case SDLK_q:
			acc.z = -setAcc;
			break;
		case SDLK_UP:
			keyAng.y = setAng;
			break;
		case SDLK_DOWN:
			keyAng.y = -setAng;
			break;
		case SDLK_LEFT:
			keyAng.x = -setAng;
			break;
		case SDLK_RIGHT:
			keyAng.x = setAng;
			break;

		default:
			break;
		}
	};
	SdlManager::onKeyChange(onKeyDown);
	Utility::startTimer();

	while (!SdlManager::shouldQuit())
	{
		float dt = Utility::restartTimer();
		SdlManager::update();
		starField.update(dt, camera);

		updateMouse(camera);

		auto &ang = camera.getAngVel();
		if (keyAng.x != 0.f)
			ang.x = keyAng.x;
		if (keyAng.y != 0.f)
			ang.y = keyAng.y;

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
