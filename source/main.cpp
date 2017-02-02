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
#include "Enemy.hpp"

#include <iostream>

int main()
{
	SdlManager::init();

	Renderer renderer(SdlManager::getSdlRenderer(), SdlManager::getSize());
	Camera camera(renderer.getSize());
	StarField starField;
	InputManager inputManager;
	Timer timer;
	
	std::vector<Enemy> enemies;
	auto space = (Vec3i() + 2 * Camera::viewDist);
	enemies.emplace_back(255, 20, 0, (space.rand() - Camera::viewDist).cast<float>());
	enemies.emplace_back(0, 255, 40, (space.rand() - Camera::viewDist).cast<float>());
	enemies.emplace_back(40, 0, 255, (space.rand() - Camera::viewDist).cast<float>());


	while (!SdlManager::shouldQuit())
	{
		float dt = timer.restart();

		// Update
		SdlManager::update();
		inputManager.update();
		starField.update(dt, camera);
		camera.update(dt, inputManager);
		for(auto &i : enemies)
			i.update(dt, camera);

		// Render
		renderer.clear(0, 0, 0);
		starField.render(renderer, camera);
		for(auto &i : enemies)
			i.render(renderer, camera);
		renderer.draw();
	}

	SdlManager::destroy();
	return 0;
}
