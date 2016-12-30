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

enum class Shape
{
	LINES, POINTS
};

class Renderer
{
public:
	Renderer(SDL_Renderer *sdlRenderer, const Vec2i &size);
	void setColor(int r, int g, int b, int a = 255);
	void clear(int r = 0, int g = 0, int b = 0, int a = 255);

	void drawSingleLine(int x1, int y1, int x2, int y2);
	void drawSinglePoint(int x, int y);
	void drawSingleFillRect(int x, int y, int w, int h);

	void beginPoints();
	void addPoint(int x, int y);
	void endPoints(Shape shape);

	void draw();
	void resize(int sx, int sy);
	int getSX();
	int getSY();
	const Vec2i &getSize();

private:
	using RenderShapesFunc = int (*)(SDL_Renderer*, const SDL_Point *points, int count);
	
	RenderShapesFunc getShapesFunc(Shape shape);

	std::vector<SDL_Point> points;
	SDL_Renderer *sdlRenderer;
	Vec2i size;
};
