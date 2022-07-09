#include <GLFW/glfw3.h>
#include <iostream>
#include <Windows.h>
#include <thread>
#include <chrono>

#include "gfx.hpp"
#include "util.hpp"

Gfx::Gfx(int width, int height) {
    if ( !glfwInit() ) {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
    }

    this->glfw_window = glfwCreateWindow( width, height, DEFAULT_TITLE, NULL, NULL );

    if (!this->glfw_window)
    {
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    glfwMakeContextCurrent(this->glfw_window);
    glfwSwapInterval( 1 );

    glfwGetFramebufferSize(this->glfw_window, &this->width, &this->height);

    glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);

    glfwMakeContextCurrent(this->glfw_window);
}

Gfx::~Gfx() {
    glfwTerminate();
};

void Gfx::setTitle(const char* title) {
    glfwSetWindowTitle(this->glfw_window, title);
}

void Gfx::clear() {
    glClearColor(
        this->backgroundColor.r,
        this->backgroundColor.g,
        this->backgroundColor.b,
        1.f
    );
}

void Gfx::pollEvents() {
    glfwPollEvents();
}

void Gfx::flip() {
    glfwSwapBuffers(this->glfw_window);
}

void Gfx::drawRect(Rect r, Color c) {
    glBegin(GL_QUADS);
    glVertex3f(r.x, r.y, 1.f);
    glVertex3f(r.x, r.y + r.h, 0.f);
    glVertex3f(r.x + r.w, r.y + r.h, 0.f);
    glVertex3f(r.x + r.w, r.y, 0.f);
    glEnd();
}

bool Gfx::shouldClose() {
    return glfwWindowShouldClose(this->glfw_window);
}
