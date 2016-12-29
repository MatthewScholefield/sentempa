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

#include <chrono>
#include <SDL2/SDL.h>
#include "Utility.hpp"

namespace Utility
{
	namespace chr = std::chrono;
	using sec = chr::seconds;
	using ns = chr::nanoseconds;
	using getTime = chr::high_resolution_clock;
	auto start=getTime::now();

	void sleep(long ms)
	{
		SDL_Delay(ms);
	}

	void startTimer()
	{
		start = getTime::now();
	}

	float restartTimer()
	{
		auto end = getTime::now();
		auto diff = end - start;
		start = end;
		return chr::duration_cast<ns>(diff).count()/(1000*1000*1000.f);
	}
}
