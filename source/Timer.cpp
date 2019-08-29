#include <chrono>
#include "Timer.hpp"
#include "types.hpp"

float Timer::restart()
{
	cauto now = Clock::now();
	cauto diff = now - last;
	last = now;
	return std::chrono::duration_cast<Dur>(diff).count();
}
