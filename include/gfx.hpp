#pragma once

// #ifndef SAMSON_GFX
// #define SAMSON_GFX

#include <GLFW/glfw3.h>
#include <time.h>
#include <thread>
#include <chrono>
#include <stdio.h>
#include <windows.h>
#include <math.h>

// #include "util.hpp"

const char* const DEFAULT_TITLE = "Title";
const int DEFAULT_WIDTH = 300;
const int DEFAULT_HEIGHT = 300;

using namespace std::chrono;


// struct Clock {
//     util::my_time start;
//     util::my_time last;

//     int total_frames;

//     Clock() { 
//         this->start = util::current_time();
//         this->last = this->start;
//         this->total_frames = 0;
//     }

//     int elapsed_ms() {
//         auto current = util::current_time();
//         auto delta = duration_cast<microseconds>(
//             current - this->last
//         ).count();

//         return delta;
//     }

//     void sleep_till_elapsed(int microseconds) {
//         int delta = this->elapsed_ms();
//         int sleep_micros = microseconds - delta - 5000;

//         std::cout << "delta is " << delta << ", sleeping for " << sleep_micros << " microseconds\n";
//         if (sleep_micros > 0) {
//             std::this_thread::sleep_for<long long, std::micro>(
//                 std::chrono::microseconds(
//                     sleep_micros
//                 )
//             );
//         }

//         while (this->elapsed_ms() < microseconds) {
//             128434908315.f / 9320580.f;
//         }
//         return;
//     }



//     int tick(int ms) {
//         this->sleep_till_elapsed(ms * 1000);
//         // std::this_thread::sleep_for<long long, std::micro>(
//         //     std::chrono::microseconds(
//         //         // x 1000 because milliseconds to microseconds
//         //         (ms * 1000) - delta
//         //     )
//         // );
//         std::cout << this->elapsed_ms() << " microseconds since last frame\n";

//         this->total_frames++;

//         int delta = this->elapsed_ms();
//         this->last = util::current_time();

//         return delta;
//     }

//     float measure_frames() {

//         return static_cast<float>(this->total_frames) /
//             std::chrono::duration_cast<std::chrono::milliseconds>(
//                 util::current_time() - this->start
//             ).count() * 1000;
//     }
// };


struct Color {
    GLfloat r;
    GLfloat g;
    GLfloat b;
};

struct Rect {
    GLfloat x;
    GLfloat y;
    GLfloat w;
    GLfloat h;
};

class Gfx
{
private:
    GLFWwindow* glfw_window;
    int width, height;
public:
    Color backgroundColor;

    Gfx(int width, int height);
    ~Gfx(); 

    void setTitle(const char* title);
    void clear();
    void flip();
    void pollEvents();

    void drawRect(Rect r, Color c);
    bool shouldClose();
};

// #endif SAMSON_GFX