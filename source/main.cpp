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
#include "InputManager.hpp"
#include "Timer.hpp"
#include "Polygon.hpp"

#include <iostream>

int main()
{
	SdlManager::init();

	Renderer renderer(SdlManager::getSdlRenderer(), SdlManager::getSize());
	Camera camera(renderer.getSize());
	StarField starField;
	InputManager inputManager;
	Timer timer;
	
	Polygon poly;
	poly.definePoint(0,{40, 0, 40});
	poly.definePoint(1,{80, 0, 100});
	poly.definePoint(2,{100, 0, 80});
	poly.definePoint(3,{55, -10, 55});
	
	poly.addFace({
		{100, 95, 95},
		{
			{0, 1, 2}
		}
	});
	poly.addFace({
		{200, 20, 0},
		{
			{0, 1, 3}
		}
	});
	poly.addFace({
		{220, 20, 0},
		{
			{0, 2, 3}
		}
	});
	poly.addFace({
		{160, 10, 0},
		{
			{1, 2, 3}
		}
	});

	while (!SdlManager::shouldQuit())
	{
		float dt = timer.restart();

		// Update
		SdlManager::update();
		inputManager.update();
		starField.update(dt, camera);
		camera.update(dt, inputManager);

		// Render
		renderer.clear(0, 0, 0);
		starField.render(renderer, camera);
		poly.render(renderer, camera);
		renderer.draw();
	}

	SdlManager::destroy();
	return 0;
}
