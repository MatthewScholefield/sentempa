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
#include <Eigen/Geometry>

#include "StarField.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"
#include "types.hpp"

void StarField::refill(const Camera &camera)
{
	auto shouldRemove = [&camera](const Star & star)
	{
		return (star.p - camera.getPos()).abs().max() > maxDepth;
	};
	stars.erase(std::remove_if(stars.begin(), stars.end(), shouldRemove),
				stars.end());

	float starsToCreate = maxStars - (int) stars.size();

	if (starsToCreate == 0)
		return;

	Box newBox = {
		camera.getPos() - maxDepth,
		{
			maxDepth * 2, maxDepth * 2, maxDepth * 2
		}
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
		cint numStars = std::round(starsToCreate * volumes[i] / totalVolume);
		const auto size = boxes[i].size.cast<int>();
		for (int j = 0; j < numStars; ++j)
			stars.push_back({boxes[i].pos + size.max(1).rand().cast<float>()});
	}
	box = newBox;
}

void StarField::update(cfloat dt, const Camera &camera)
{
	for (Star &i : stars)
		i.update(dt);

	refill(camera);
}

void StarField::render(Renderer &renderer, const Camera &camera) const
{
	const auto canvasSize = renderer.getSize().cast<float>();
	for (const Star &i : stars)
	{
		const Vec2f pt = camera.projectPoint(i.p, canvasSize);
		if (std::isnan(pt.x))
			continue;

		cfloat dist = i.p.dist(camera.getPos());
		cint squareSize = dist == 0.f ? 0 : std::max(1.f, starSize / dist);

		if (pt.x + squareSize < 0.f || pt.x >= canvasSize.x ||
				pt.y + squareSize < 0.f || pt.y >= canvasSize.y)
			continue;

		int alpha = 255.f * (1.f - dist / (sqrt(maxDepth * maxDepth)));
		if (alpha <= 0)
			continue;

		int r = 255, g = 255, b = 255;
		cint twinkle = rand() % 301 - 150;
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
		renderer.drawSingleFillRect(pt.x, pt.y, squareSize, squareSize);
	}
}

void StarField::Star::update(cfloat dt) { }

bool StarField::Star::shouldRemove(const Vec2i &size) const
{
	return p.x < 0 || p.x >= size.x ||
			p.y < 0 || p.y >= size.y;
}

