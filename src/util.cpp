#include <chrono>
#include <time.h>
#include <windows.h>

#include <iostream>

#include "util.hpp"

inline util::my_time now() {
    return std::chrono::high_resolution_clock::now();
}

Clock::Clock() {
    this->start_time = now();
    this->last_time = this->start_time;
    this->frames = 0;
    this->last_fps_update_time = this->start_time;
    this->fps_update_freq = 5;
}

void Clock::tick(double seconds) {
    using namespace std::chrono;

    auto time_to_sleep = seconds - (now() - this->last_time).count() / 1e9;
    util::timerSleep(time_to_sleep);
    this->last_time +=std::chrono::nanoseconds(
        static_cast<long long>(seconds * 1e9)
    );

    this->frames++;
    if (this->frames % this->fps_update_freq == 0) {
        this->fps = this->fps_update_freq / ((now() - this->last_fps_update_time).count() * 1e-9);
        this->last_fps_update_time = now();
    }
}

namespace util {
    my_time current_time() {
        return std::chrono::high_resolution_clock::now();
    }

    int get_the_millis(my_duration d) {
        return std::chrono::duration_cast<std::chrono::milliseconds>(d).count();
    }

    void timerSleep(double seconds) {
        using namespace std::chrono;

        auto the_start = high_resolution_clock::now();

        static HANDLE timer = CreateWaitableTimer(NULL, FALSE, NULL);
        static double estimate = 5e-3;
        static double mean = 5e-3;
        static double m2 = 0;
        static int64_t count = 1;

        while (seconds - estimate > 1e-7) {
            double toWait = seconds - estimate;
            LARGE_INTEGER due;
            due.QuadPart = -int64_t(toWait * 1e7);
            auto start = high_resolution_clock::now();
            SetWaitableTimerEx(timer, &due, 0, NULL, NULL, NULL, 0);
            WaitForSingleObject(timer, INFINITE);
            auto end = high_resolution_clock::now();

            double observed = (end - start).count() / 1e9;
            seconds -= observed;

            ++count;
            double error = observed - toWait;
            double delta = error - mean;
            mean += delta / count;
            m2   += delta * (error - mean);
            double stddev = sqrt(m2 / (count - 1));
            estimate = mean + stddev;
        }

        // spin lock
        auto start = high_resolution_clock::now();
        while ((high_resolution_clock::now() - start).count() / 1e9 < seconds);

        // auto the_end = high_resolution_clock::now();
        // std::cout << "hello";
        // std::cout << "\n\n" << duration_cast<microseconds>(the_start - the_end).count() << "\n";
    }
}
