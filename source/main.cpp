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
	enemies.emplace_back(255, 20, 0, (space.rand() - Camera::viewDist).cast<float>(), 0.8f, 80);
	enemies.emplace_back(0, 255, 40, (space.rand() - Camera::viewDist).cast<float>(), 0.5f, 50);
	enemies.emplace_back(40, 0, 255, (space.rand() - Camera::viewDist).cast<float>(), 1.2f, 100);


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
