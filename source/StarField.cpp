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

void StarField::update(float dt, Vec2i size, Camera &camera)
{
	camera.pos.z += 100.f * dt;
	for (Star &i : stars)
		i.update(dt);

	auto shouldRemove = [&camera](const Star & star)
	{
		return star.p.z < camera.pos.z;
	};
	stars.erase(std::remove_if(stars.begin(), stars.end(), shouldRemove),
				stars.end());

	for (int i = 0; i < stars.size() - maxStars; ++i)
	{
		const float x = rand() % size.x - size.x/2;
		const float y = rand() % size.y - size.y/2;
		const float z = rand() % maxDepth + camera.pos.z;

		stars.push_back({
			{x, y, z}
		});
	}
}

void StarField::render(Renderer &renderer, Camera &camera) const
{
	renderer.setColor(255, 255, 255);
	renderer.beginPoints();
	{
		for (const Star &i : stars)
		{
			float angleHoriz = atan2(i.p.x - camera.pos.x, i.p.z - camera.pos.z);
			float renderPx = (angleHoriz / camera.fov + 0.5f) * renderer.getSX();
			
			float angleVert = atan2(i.p.y - camera.pos.y, i.p.z - camera.pos.z);
			float renderPy = (angleVert / camera.fov + 0.5f) * renderer.getSY();
			
			renderer.addPoint(renderPx, renderPy);
		}
	}
	renderer.endPoints(Shape::POINTS);
}

void StarField::Star::update(float dt)
{
}

bool StarField::Star::shouldRemove(Vec2i size) const
{
	return p.x < 0 || p.x >= size.x ||
			p.y < 0 || p.y >= size.y;
}

