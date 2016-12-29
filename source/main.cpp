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

#include "SdlManager.hpp"
#include "Renderer.hpp"
#include "Utility.hpp"

int main()
{
	SdlManager::init();
	const auto size = SdlManager::getSize();
	Renderer renderer(SdlManager::getSdlRenderer(), size.first, size.second);

	while (!SdlManager::shouldQuit())
	{
		SdlManager::update();
		
		renderer.clear(90, 10, 10);
		{
			renderer.setColor(10, 110, 200);
			renderer.beginPoints();
			{
				for (int i = 0; i < 20000; ++i)
					renderer.addPoint(rand() % size.first, rand() % size.second);
			}
			renderer.endPoints(Shape::LINES);
		}
		renderer.draw();
		Utility::sleep(1);
	}

	SdlManager::destroy();
	return 0;
}
