#include <iostream>
#include <string>
#include <GLFW/glfw3.h>

static void
cube(GLfloat x, GLfloat y, GLfloat z, GLfloat r);

static void
draw() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cube(5.0, 5.0, 0.0, 9.0);
}

static void
cube(GLfloat x, GLfloat y, GLfloat z, GLfloat r)
{
	glShadeModel(GL_FLAT);
	GLfloat half_r = r / 2.f;

	// TODO: What does this do?
	glNormal3f(0.f, 0.f, 1.f);

	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(x - half_r, y - half_r, z);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(x - half_r, y + half_r, z);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(x + half_r, y + half_r, z);
	glVertex3f(x + half_r, y - half_r, z);

	glEnd();

}

/* change view angle, exit upon ESC */
void key( GLFWwindow* window, int k, int s, int action, int mods )
{
  if( action != GLFW_PRESS ) return;

  switch (k) {
  case GLFW_KEY_ESCAPE:
    glfwSetWindowShouldClose(window, GLFW_TRUE);
    break;
  default:
    return;
  }
}

int main(int argc, char *argv[])
{
    GLFWwindow* window;
    int width, height;

    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
    }

    window = glfwCreateWindow( 300, 300, "Gears", NULL, NULL );
    if (!window)
    {
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval( 1 );

    glfwGetFramebufferSize(window, &width, &height);

	glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);

    // Parse command-line options
    // Main loop
    while( !glfwWindowShouldClose(window) )
    {
		draw();

		glfwSetKeyCallback(window, key);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    // Exit program
    exit( EXIT_SUCCESS );
}

