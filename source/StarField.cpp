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

void StarField::update(float dt, Vec2i size)
{
	for (Star &i : stars)
		i.update(dt);

	auto shouldRemove = [&size](const Star & star)
	{
		return star.shouldRemove(size);
	};
	stars.erase(std::remove_if(stars.begin(), stars.end(), shouldRemove),
				stars.end());

	for (int i = 0; i < stars.size() - maxStars; ++i)
	{
		const float x = size.x / 2.f, vx = rand() % 200 - 100;
		const float y = size.y / 2.f, vy = rand() % 200 - 100;

		stars.push_back({
			{x, y},
			{vx, vy}
		});
	}
}

void StarField::render(Renderer &renderer)
{
	renderer.setColor(255, 255, 255);
	renderer.beginPoints();
	{
		for (const Star &i : stars)
			renderer.addPoint(i.p.x, i.p.y);
	}
	renderer.endPoints(Shape::POINTS);
}

void StarField::Star::update(float dt)
{
	p += v * dt;
}

bool StarField::Star::shouldRemove(Vec2i size) const
{
	return p.x < 0 || p.x >= size.x ||
			p.y < 0 || p.y >= size.y;
}

