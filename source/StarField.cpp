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

#include <algorithm>

#include "StarField.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"

void StarField::populate(Vec2i size, Camera& camera, bool randZ)
{
	const Vec2f &fov = camera.getFov();
	int spawnSx = 2 * maxDepth * tan(fov.x / 2);
	int spawnSy = 2 * maxDepth * tan(fov.y / 2);
	for (int i = 0; i < stars.size() - maxStars; ++i)
	{
		const float x = rand() % spawnSx - spawnSx / 2.f;
		const float y = rand() % spawnSy - spawnSy / 2.f;
		const float z = randZ ? rand() % maxDepth : maxDepth + camera.pos.z;

		stars.push_back({
			{x, y, z}
		});
	}
}

void StarField::update(float dt, Vec2i size, Camera &camera)
{
	for (Star &i : stars)
		i.update(dt);

	auto shouldRemove = [&camera](const Star & star)
	{
		return star.p.z < camera.pos.z;
	};
	stars.erase(std::remove_if(stars.begin(), stars.end(), shouldRemove),
				stars.end());

	populate(size, camera, stars.size() == 0);
}

void StarField::render(Renderer &renderer, Camera &camera) const
{
	const Vec2f size(renderer.getSize().cast<float>());
	for (const Star &i : stars)
	{
		const float dz = i.p.z - camera.pos.z;
		const float ax = atan2(i.p.x - camera.pos.x, dz);
		const float ay = atan2(i.p.y - camera.pos.y, dz);

		const Vec2f pt = (Vec2f({ax, ay}) / camera.getFov() + 0.5f) * size;
		const int alpha = 255.f * std::min(1.f, 1.f * (1.f - (i.p.z - camera.pos.z) / maxDepth));
		int r = 255, g = 255, b = 255;
		const int twinkle = rand() % 501 - 250;
		if (twinkle > 0)
		{
			r -= twinkle;
			g -= twinkle;
		}
		else
		{
			g += twinkle / 2;
			b += twinkle;
		}
		renderer.setColor(r, g, b, alpha);
		const float dist = i.p.dist(camera.pos);
		const int size = std::max(1.f, 800.f/dist);
		renderer.drawSingleFillRect(pt.x, pt.y, size, size);
	}
}

void StarField::Star::update(float dt) { }

bool StarField::Star::shouldRemove(Vec2i size) const
{
	return p.x < 0 || p.x >= size.x ||
			p.y < 0 || p.y >= size.y;
}

