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
#include <iostream>
#include "Polygon.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"
#include "StarField.hpp"

Triangle::Triangle(const Vec3<uint8_t> &color, const std::array<size_t, 3> &ids) :
color(color), ids(ids) { }

void Triangle::draw(Renderer& renderer, const Camera &camera, const std::vector<Vec3f> &pts) const
{
	cauto canvasSize = renderer.getSize().cast<float>();
	cauto dist = pts[ids[0]].dist(camera.getPos());
	if (dist > Camera::viewDist)
		return;

	std::array<Vec2f, 3> triPts;

	bool offScreen = true;
	for (int i = 0; i < 3; ++i)
	{
		cauto proj = camera.projectPoint(pts[ids[i]], canvasSize);
		triPts[i] = proj.pt;
		if (proj.onScreen)
			offScreen = false;
	}
	if (offScreen)
		return;
	int alpha = 255.f * (1.f - dist / Camera::viewDist);

	renderer.drawFillTri(triPts, makeCol(color.x, color.y, color.z, alpha));
}

int t = 0;

RenderOrder Triangle::calcRenderOrder(const Triangle& other, const Camera& camera, const std::vector<Vec3f>& pts) const
{
	size_t mDiffPId = 7;
	for (int pId = 0; pId < 3; ++pId)
	{
		bool isUnique = true;
		for (int oPId = 0; oPId < 3; ++oPId)
		{
			if (ids[pId] == other.ids[oPId])
			{
				isUnique = false;
				break;
			}
		}
		if (isUnique)
		{
			mDiffPId = pId;
			break;
		}
	}

	Vec2<size_t> mAxisPIds = mDiffPId != 0 ? (mDiffPId != 1 ?
			Vec2<size_t>(0, 1) :
			Vec2<size_t>(0, 2)) :
			Vec2<size_t>(1, 2);
	size_t oDiffPId = ids[mAxisPIds.x] == other.ids[0] ?
			(ids[mAxisPIds.y] == other.ids[1] ? 2 : 1) : 0;

	cauto &axisPt1 = pts[ids[mAxisPIds.x]];
	cauto &axisPt2 = pts[ids[mAxisPIds.y]];
	cauto axis = axisPt2 - axisPt1;

	cfloat dotMag = axis.dotP(axis);

	auto orthoVec = [&](const Vec3f & p)
	{
		return p - (axisPt1 + axis * ((p - axisPt1).dotP(axis) / dotMag));
	};

	cauto camDir = orthoVec(camera.getPos());

	cauto mDir = orthoVec(pts[ids[mDiffPId]]);
	cauto oDir = orthoVec(pts[other.ids[oDiffPId]]);

	cfloat camMag = camDir.mag();

	cfloat mAngle = acos(camDir.dotP(mDir) / (mDir.mag() * camMag));
	cfloat oAngle = acos(camDir.dotP(oDir) / (oDir.mag() * camMag));

	auto ts = [](const Vec3f & f)
	{
		Vec3i a = f.cast<int>();
		return std::to_string(a.x) + ", " +
				std::to_string(a.y) + ", " +
				std::to_string(a.z);
	};

	auto tsIds = [&](const std::array<size_t, 3> &ids)
	{
		return "{(" + ts(pts[ids[0]]) + "), (" + ts(pts[ids[1]]) + "), (" + ts(pts[ids[2]]) + ")}";
	};

	return mAngle < oAngle ? RenderOrder::before : RenderOrder::after;
}

void Polygon::render(Renderer &renderer, const Camera &camera) const
{
	using Entry = std::pair<size_t, float>;
	std::vector<size_t> renderOrder;
	renderOrder.reserve(triangles.size());
	for (size_t i = 0; i < triangles.size(); ++i)
	{
		auto it = renderOrder.begin();
		for (;; ++it)
		{
			if (it == renderOrder.end() || triangles[i].calcRenderOrder(triangles[*it], camera, pts) == RenderOrder::before)
			{
				renderOrder.insert(it, i);
				break;
			}
		}
	}

	for (auto it = renderOrder.rbegin(); it != renderOrder.rend(); ++it)
		triangles[*it].draw(renderer, camera, pts);
}

void Polygon::definePoint(size_t id, const Vec3f& pt)
{
	if (id != pts.size())
		throw std::logic_error("Point ids not in consecutive order!");
	pts.emplace_back(pt);
}

void Polygon::addFace(const Triangle &tri)
{
	triangles.push_back(tri);
}

