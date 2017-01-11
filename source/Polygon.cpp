/*
 * Copyright (C) 2017 Matthew D. Scholefield
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

#include <vector>
#include "Polygon.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"
#include "StarField.hpp"

Polygon::Polygon()
{
	Triangle t{
		{
			{0, 0, 0},
			{0, 0, 10},
			{10, 0, 0}
		}
	};
	triangles.push_back(t);
}

void Polygon::render(Renderer &renderer, const Camera &camera) const
{
	cauto canvasSize = renderer.getSize().cast<float>();
	for (auto &tri : triangles)
	{
		cauto dist = tri[0].dist(camera.getPos());
		cauto maxDist = sqrt(StarField::maxDepth * StarField::maxDepth);
		if (dist > maxDist)
			continue;
		
		std::array<Vec2f, 3> triPts;

		bool offScreen = true;
		bool undef = false;
		for (int i = 0; i < 3; ++i)
		{
			triPts[i] = camera.projectPoint(tri[i], canvasSize);
			if (triPts[i].x > 0 && triPts[i].x < canvasSize.x &&
					triPts[i].y > 0 && triPts[i].y < canvasSize.y)
				offScreen = false;
			if (isnanf(triPts[i].x) ||isnanf(triPts[i].y))
				undef = true;
		}
		if (undef)
			offScreen = true;
		if (offScreen)
			continue;
		int alpha = 255.f * (1.f - dist / maxDist);

		renderer.drawTri(triPts, makeCol(190, 20, 10, alpha));
	}
}

