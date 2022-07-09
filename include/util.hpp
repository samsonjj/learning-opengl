#pragma once

#include <chrono>
#include <time.h>
#include <windows.h>

namespace util {
    using my_time = std::chrono::steady_clock::time_point;
    using my_duration = std::chrono::steady_clock::duration;

    my_time current_time();

    int get_the_millis(my_duration d);

    void timerSleep(double seconds);
}

struct Clock {
    util::my_time start_time;
    util::my_time last_time;

    // framerate calculation
    util::my_time last_fps_update_time;
    double fps;
    long long fps_update_freq;
    long long frames;

    Clock();

    void tick(double seconds);
};

