#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include <thread>

const int WIN_WIDTH = 1024;
const int WIN_HEIGHT = 620;
const char* WIN_TITLE = "sphere demo";

const GLfloat RED[] = { 1.0, 0.0, 0.0 };
const GLfloat WHITE[] = { 1.0, 1.0, 1.0 };
const GLfloat BLUE[] = { 0.0, 1.0, 0.0 };
const GLfloat GREEN[] = { 0.0, 0.0, 1.0 };
const GLfloat YELLOW[] = { 1.0, 1.0, 0.0 };
const GLfloat PURPLE[] = { 1.0, 0.0, 1.0 };
const GLfloat IDK[] = { .0, 1.0, 1.0 };

void terminate(int error_code) {
    glfwTerminate();
    exit(error_code);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE) {

    }
}

GLFWwindow* initWindow() {
    if (!glfwInit()) {
        fprintf(stderr, "Could not intialize GLFW\n");
        exit(EXIT_FAILURE);
    }
    
    auto window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE, NULL, NULL);
    if (!window) {
        fprintf(stderr, "Could not initialize GLFW window");
        terminate(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_DEPTH_BITS, 16);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwSwapInterval( 1 );

    glfwMakeContextCurrent(window);

    // http://www.opengl-tutorial.org/beginners-tutorials/tutorial-4-a-colored-cube/
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    GLfloat scale = static_cast<float>(WIN_WIDTH) / WIN_HEIGHT;
    glOrtho(-1.0 * scale, 1.0 * scale, -1.0, 1.0, -1.0, 1.0);

    glfwSetKeyCallback(window, keyCallback);

    return window;
}

void drawCube(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat a) {
   
    glColor3f(1.f, 1.f, 1.f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glScaled(r, r, r);
        glRotated(a, 1.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            // FRONT FACE
            glColor3fv(RED);
            glVertex3f(-1, -1, -1);
            glVertex3f(-1, 1, -1);
            glVertex3f(1, 1, -1);
            glVertex3f(1, -1, -1);

            // LEFT FACE
            glColor3fv(BLUE);
            glVertex3f(-1, -1, 1);
            glVertex3f(-1, 1, 1);
            glVertex3f(-1, 1, -1);
            glVertex3f(-1, -1, -1);

            // BACK FACE
            glColor3fv(GREEN);
            glVertex3f(1, -1, 1);
            glVertex3f(1, 1, 1);
            glVertex3f(-1, 1, 1);
            glVertex3f(-1, -1, 1);

            // RIGHT FACE
            glColor3fv(YELLOW);
            glVertex3f(1, -1, -1);
            glVertex3f(1, 1, -1);
            glVertex3f(1, 1, 1);
            glVertex3f(1, -1, 1);

            // TOP FACE
            glColor3fv(PURPLE);
            glVertex3f(-1, 1, -1);
            glVertex3f(-1, 1, 1);
            glVertex3f(1, 1, 1);
            glVertex3f(1, 1, -1);
            
            // BOTTOM FACE
            glColor3fv(IDK);
            glVertex3f(-1, -1, 1);
            glVertex3f(-1, -1, -1);
            glVertex3f(1, -1, -1);
            glVertex3f(1, -1, 1);
            

        glEnd();
    glPopMatrix();
}

void display(GLFWwindow* window) {

    glClearColor(.5, .2, .2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    static float a = 0.0;

    drawCube(0.0, 0.0, 0.0, .2, a);

    glfwPollEvents();
    glfwSwapBuffers(window);

    a += 0.3;
}

struct MassiveObject {
    float mass;
};

int main() {
    auto window = initWindow();

    while (!glfwWindowShouldClose(window)) {
        display(window);
    }

    terminate(0);
}
