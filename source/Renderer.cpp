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

#include "types.hpp"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "Renderer.hpp"
#include "SdlManager.hpp"

Renderer::Renderer(SDL_Renderer *sdlRenderer, const Vec2i &size) :
sdlRenderer(sdlRenderer), size(size)
{
	SdlManager::onResize([this](cint sx, cint sy)
	{
		resize(sx, sy);
	});
}

void Renderer::setColor(cint r, cint g, cint b, cint a)
{
	SDL_SetRenderDrawColor(sdlRenderer, r, g, b, a);
}

void Renderer::clear(cint r, cint g, cint b, cint a)
{
	setColor(r, g, b, a);
	SDL_RenderClear(sdlRenderer);
}

void Renderer::drawSingleLine(cint x1, cint y1, cint x2, cint y2, const colInt col)
{
	lineColor(sdlRenderer, x1, y1, x2, y2, col);
}

void Renderer::drawSinglePoint(cint x, cint y, const colInt col)
{
	pixelColor(sdlRenderer, x, y, col);
}

void Renderer::drawFillSquare(cint x, cint y, cint rad, const colInt col)
{
	boxColor(sdlRenderer, x, y, x + rad - 1, y + rad - 1, col);
}

void Renderer::drawFillTri(const std::array<Vec2f, 3>& pts, const colInt col)
{
	filledTrigonColor(sdlRenderer, pts[0].x, pts[0].y, pts[1].x, pts[1].y, pts[2].x, pts[2].y, col);
}

void Renderer::beginPoints()
{
	points.clear();
}

void Renderer::addPoint(cint x, cint y)
{
	points.push_back({x, y});
}

void Renderer::endPoints(Shape shape)
{
	auto func = getShapesFunc(shape);
	func(sdlRenderer, points.data(), points.size());
}

void Renderer::draw()
{
	SDL_RenderPresent(sdlRenderer);
}

void Renderer::resize(cint sx, cint sy)
{
	size = {sx, sy};
}

int Renderer::getSX() const
{
	return size.x;
}

int Renderer::getSY() const
{
	return size.y;
}

const Vec2i & Renderer::getSize() const
{
	return size;
}

Renderer::RenderShapesFunc Renderer::getShapesFunc(Shape shape) const
{
	switch (shape)
	{
	case Shape::LINES:
		return &SDL_RenderDrawLines;
	case Shape::POINTS:
		return &SDL_RenderDrawPoints;
	}
}

