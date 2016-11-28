#include "Timer.hpp"

gol::Timer::Timer()
{
}

gol::Timer::~Timer()
{
}

void gol::Timer::start()
{
    is_stopped = false;
    begin = high_resolution_clock::now();
}

void gol::Timer::stop()
{
    is_stopped = true;
    end = high_resolution_clock::now();
}

long long gol::Timer::get_elapsed_time()
{
    high_resolution_clock::time_point end_time;

    if (!is_stopped)
    {
        end_time = high_resolution_clock::now();
    }
    else
    {
        end_time = end;
    }

    return static_cast<long long>(std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin).count());
}
