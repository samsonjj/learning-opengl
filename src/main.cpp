#include <GLFW/glfw3.h>
#include <iostream>

#include "gfx.hpp"
#include "util.hpp"

int main() {
	Gfx gfx(300, 300);

	Clock clock;

	int frames = 0;
	auto startTime = util::current_time();
	auto last_time = util::current_time();

    while( !gfx.shouldClose() )
    {
		double time_passed = util::get_the_millis(util::current_time() - startTime) / 1000.f;
		double fps = frames / time_passed;

		std::cout << "fps: " << clock.fps << "\n";

		clock.tick(1 / 60.f);
		gfx.pollEvents();
		gfx.drawRect(Rect{ 2, 2, 5, 5 }, Color{ 1.f, 1.f, 1.f });
		gfx.flip();

		frames++;
    }
}
