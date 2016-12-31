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

#include <memory>

#include "StarField.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"

void StarField::refill(Camera &camera)
{
	auto shouldRemove = [&camera](const Star & star)
	{
		return (star.p - camera.p).abs().max() > maxDepth;
	};
	stars.erase(std::remove_if(stars.begin(), stars.end(), shouldRemove),
				stars.end());

	float starsToCreate = maxStars - (int) stars.size();

	if (starsToCreate == 0)
		return;

	Box newBox = {
		camera.p - maxDepth,
		{maxDepth * 2, maxDepth * 2, maxDepth * 2}
	};

	// Delta
	Vec3f d = newBox.pos - box.pos;
	Vec3f da = d.abs();
	Vec3f &s = newBox.size;

	std::array<Box, 3> boxes;

	boxes[0].size = {da.x, s.y, s.z};
	boxes[1].size = {s.x - da.x, da.y, s.z};
	boxes[2].size = {s.x - da.x, s.y - da.y, da.z};

	boxes[0].pos = box.pos + (d.x > 0.f ? Vec3f(box.size.x, 0.f, 0.f) : Vec3f(d.x, d.y, d.z));
	boxes[1].pos = box.pos + (d.y > 0.f ? Vec3f(0.f, box.size.y, 0.f) : Vec3f(0.f, d.y, d.z));
	boxes[2].pos = box.pos + (d.z > 0.f ? Vec3f(0.f, 0.f, box.size.z) : Vec3f(0.f, 0.f, d.z));

	if (box.size.volume() == 0.f)
	{
		boxes[0] = newBox;
		boxes[1] = boxes[2] = Box();
	}

	float totalVolume = 0.f;
	std::array<float, boxes.size() > volumes;
	for (int i = 0; i < volumes.size(); ++i)
		totalVolume += (volumes[i] = boxes[i].size.volume());

	for (int i = 0; i < boxes.size(); ++i)
	{
		const int numStars = std::round(starsToCreate * volumes[i] / totalVolume);
		for (int j = 0; j < numStars; ++j)
		{
			const auto size = boxes[i].size.cast<int>();
			stars.push_back({boxes[i].pos + size.max(1).rand().cast<float>()});
		}
	}
	box = newBox;
}

void StarField::update(float dt, Camera &camera)
{
	for (Star &i : stars)
		i.update(dt);

	refill(camera);
}

void StarField::render(Renderer &renderer, Camera &camera) const
{
	const Vec2f size(renderer.getSize().cast<float>());
	for (const Star &i : stars)
	{
		const float dz = i.p.z - camera.p.z;
		const float ax = atan2(i.p.x - camera.p.x, dz);
		const float ay = atan2(i.p.y - camera.p.y, dz);

		const Vec2f pt = (Vec2f({ax, ay}) / camera.getFov() + 0.5f) * size;
		const int alpha = 255.f * std::min(1.f, 1.f * (1.f - (i.p.z - camera.p.z) / maxDepth));
		int r = 255, g = 255, b = 255;
		const int twinkle = rand() % 301 - 150;
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
		const float dist = i.p.dist(camera.p);
		const int size = dist == 0.f ? 0 : std::max(1.f, starSize / dist);
		renderer.drawSingleFillRect(pt.x, pt.y, size, size);
	}
}

void StarField::Star::update(float dt) { }

bool StarField::Star::shouldRemove(Vec2i size) const
{
	return p.x < 0 || p.x >= size.x ||
			p.y < 0 || p.y >= size.y;
}

