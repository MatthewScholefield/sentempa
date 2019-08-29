#pragma once

#include <chrono>

class Timer
{
	using sec = std::chrono::seconds;
	using Dur = std::chrono::duration<float>;
	using Resolution = std::chrono::nanoseconds;
	using Clock = std::chrono::high_resolution_clock;
	using TimePoint = std::chrono::time_point<Clock, Resolution>;

public:
	float restart();

private:
	TimePoint last = Clock::now();
};
