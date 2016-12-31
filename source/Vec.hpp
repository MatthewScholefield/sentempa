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

#include "Vec.inl"

template<typename T>
class Vec2
{
public:
	CREATE_CONSTRUCTORS(2);
	CREATE_ALL_OPERATORS(2);
	CREATE_CAST_FN(2);
	CREATE_DIST_FNS(2);
	CREATE_VOLUME_FN(2);
	CREATE_ABS_FN(2);
	CREATE_MIN_MAX_FN(2);
	CREATE_RAND_FN(2);
	
	T x, y;
};

template<typename T>
class Vec3
{
public:
	CREATE_ALL_OPERATORS(3);
	CREATE_CONSTRUCTORS(3);
	CREATE_CAST_FN(3);
	CREATE_DIST_FNS(3);
	CREATE_VOLUME_FN(3);
	CREATE_ABS_FN(3);
	CREATE_MIN_MAX_FN(3);
	CREATE_RAND_FN(3);
	
	T x, y, z;
};

using Vec2i = Vec2<int>;
using Vec2f = Vec2<float>;
using Vec3i = Vec3<int>;
using Vec3f = Vec3<float>;
