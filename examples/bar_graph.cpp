#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include <vector>
#include <stdlib.h>
#include <time.h>

struct Rect
{
	GLfloat x;
	GLfloat y;
	GLfloat w;
	GLfloat h;
};

static void
cube(GLfloat x, GLfloat y, GLfloat z, GLfloat r);

static void
bar_graph(std::vector<GLfloat> data, Rect dims);

static GLfloat
randf() {
	return ((float) rand()) / RAND_MAX;
}

static void
draw() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// cube(5.0, 5.0, 0.0, 9.0);
}

template <typename T>
static T
max(std::vector<T> data) {
	GLfloat result = data[0];
	for (int i = 0; i < data.size(); i++) {
		if (data[i] > result) {
			result = data[i];
		}
	}
	return result;
}

static void
bar_graph(std::vector<GLfloat> data, std::vector<std::vector<GLfloat>> colors, Rect dims) {
	glBegin(GL_QUADS);
	int offset = 0;
	int max_val = max(data);
	GLfloat bar_width = dims.w / data.size();
	for (int i = 0; i < data.size(); i++) {
		GLfloat val = data[i];
		std::cout << colors[i][0] << colors[i][1] << colors[i][2] << "\n";
		glColor3f(colors[i][0], colors[i][1], colors[i][2]);
		glVertex3f(offset * bar_width, 0.f, 0.f);
		glVertex3f(offset * bar_width, (val / max_val) * dims.h, 0.f);
		glVertex3f(offset * bar_width + bar_width, (val / max_val) * dims.h, 0.f);
		glVertex3f(offset * bar_width + bar_width, 0.f, 0.f);
		offset++;
	}
	glEnd();
}

static void
cube(GLfloat x, GLfloat y, GLfloat z, GLfloat r)
{
	glShadeModel(GL_FLAT);
	glColor3f(0.0, 1.0, 0.0);

	// This sets the normal vector of verticies;
	// (0, 0, 1) points outwards towards us (the viewer)
	glNormal3f(0.f, 0.f, 1.f);

	GLfloat half_r = r / 2.f;

	// http://www.cs.uccs.edu/~ssemwal/glman.html#:~:text=GL_QUADS%20Treats%20each%20group%20of,a%20connected%20group%20of%20quadrilaterals
	glBegin(GL_QUAD_STRIP);
	glVertex3f(x - half_r, y - half_r, z);
	glVertex3f(x - half_r, y + half_r, z);
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
	srand(time(NULL));
    GLFWwindow* window;
    int width, height;

	if ( !glfwInit() ) {
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

	std::vector data{1.f, 2.f, 3.f, 4.f};

	std::vector<std::vector<GLfloat>> colors{};
	for (int i = 0; i < data.size(); i++) {
		colors.push_back(std::vector{randf(), randf(), randf()});
	}

    // Parse command-line options
    // Main loop
    while( !glfwWindowShouldClose(window) )
    {
		glfwSetKeyCallback(window, key);

		draw();
		bar_graph(data, colors, Rect{ 0.0, 0.0, 9.0, 9.0 });

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    // Exit program
    exit( EXIT_SUCCESS );
}
