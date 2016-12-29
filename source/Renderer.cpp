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

#include <SDL2/SDL_render.h>
#include "Renderer.hpp"

Renderer::Renderer(SDL_Renderer *sdlRenderer, int sx, int sy) :
sdlRenderer(sdlRenderer), sx(sx), sy(sy) { }

void Renderer::setColor(int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(sdlRenderer, r, g, b, a);
}

void Renderer::clear(int r, int g, int b, int a)
{
	setColor(r, g, b, a);
	SDL_RenderClear(sdlRenderer);
}

void Renderer::drawSingleLine(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLine(sdlRenderer, x1, y1, x2, y2);
}

void Renderer::drawSinglePoint(int x, int y)
{
	SDL_RenderDrawPoint(sdlRenderer, x, y);
}

void Renderer::beginPoints()
{
	points.clear();
}

void Renderer::addPoint(int x, int y)
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

void Renderer::resize(int sx, int sy)
{
	this->sx = sx;
	this->sy = sy;
}

int Renderer::getSX()
{
	return sx;
}

int Renderer::getSY()
{
	return sy;
}

Renderer::RenderShapesFunc Renderer::getShapesFunc(Shape shape)
{
	switch (shape)
	{
	case Shape::LINES:
		return &SDL_RenderDrawLines;
	case Shape::POINTS:
		return &SDL_RenderDrawPoints;
	}
}

