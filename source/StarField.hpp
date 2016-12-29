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

#include "Vec2.hpp"

class Renderer;

class StarField
{
public:
	void update(float dt, Vec2<int> size);
	void render(Renderer &renderer);

private:
	static constexpr int maxStars = 1000;

	class Star
	{
	public:
		void update(float dt);
		bool shouldRemove( Vec2<int> size) const;
		Vec2<float> p, v;
	};
	std::vector<Star> stars;
};
