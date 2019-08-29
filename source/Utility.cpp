#include <SDL2/SDL.h>
#include "Utility.hpp"

namespace Utility
{
	void sleep(const long ms)
	{
		SDL_Delay(ms);
	}
}
