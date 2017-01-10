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

#pragma once

#include <vector>
#include <SDL2/SDL_render.h>
#include "Vec.hpp"
#include "types.hpp"

enum class Shape
{
	LINES, POINTS
};

class Renderer
{
public:
	Renderer(SDL_Renderer *sdlRenderer, const Vec2i &size);
	void setColor(cint r, cint g, cint b, cint a = 255);
	void clear(cint r = 0, cint g = 0, cint b = 0, cint a = 255);

	void drawSingleLine(cint x1, cint y1, cint x2, cint y2);
	void drawSinglePoint(cint x, cint y);
	void drawSingleFillRect(cint x, cint y, cint w, cint h);

	void beginPoints();
	void addPoint(cint x, cint y);
	void endPoints(Shape shape);

	void draw();
	void resize(cint sx, cint sy);
	int getSX() const;
	int getSY() const;
	const Vec2i &getSize() const;

private:
	using RenderShapesFunc = int (*)(SDL_Renderer*, const SDL_Point *points, int count);

	RenderShapesFunc getShapesFunc(Shape shape) const;

	std::vector<SDL_Point> points;
	SDL_Renderer *sdlRenderer;
	Vec2i size;
};
