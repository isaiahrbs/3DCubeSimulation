#include <stdio.h>
#include <math.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
#include "points.h"

float A = 0, B = 0, C = 0;


float rotateX(float i, float j, float k) {
	return j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) +
		   j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}

float rotateY(float i, float j, float k) {
	return j * cos(A) * cos(C) + k * sin(A) * cos(C) - j * sin(A) * sin(B) * 
		   sin(C) + k * cos(A) * sin(B) * sin(C) - i * cos(B) * sin(C);
}

float rotateZ(float i, float j, float k) {
	return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}

void set_all_points(point_s* points) {
    // Cube centré, plus grand pour bien voir la perspective
    points[0].x = -10.0f; points[0].y = -10.0f; points[0].z = -10.0f;
    points[1].x =  10.0f; points[1].y = -10.0f; points[1].z = -10.0f;
    points[2].x =  10.0f; points[2].y =  10.0f; points[2].z = -10.0f;
    points[3].x = -10.0f; points[3].y =  10.0f; points[3].z = -10.0f;

    points[4].x = -10.0f; points[4].y = -10.0f; points[4].z =  10.0f;
    points[5].x =  10.0f; points[5].y = -10.0f; points[5].z =  10.0f;
    points[6].x =  10.0f; points[6].y =  10.0f; points[6].z =  10.0f;
    points[7].x = -10.0f; points[7].y =  10.0f; points[7].z =  10.0f;
}

void rotate_all_points(point_s* points) {
	for (int i = 0; i < 8; i++) {
		// coordonnées originales
		float orig_x = points[i].x;
		float orig_y = points[i].y;
		float orig_z = points[i].z;
		
		// les nouvelles coordonnées après rotation
		points[i].x = rotateX(orig_x, orig_y, orig_z);
		points[i].y = rotateY(orig_x, orig_y, orig_z);
		points[i].z = rotateZ(orig_x, orig_y, orig_z);

		printf("Point %i (x%.2f, y%.2f, z%.2f)\n", i, points[i].x, points[i].y, points[i].z);
	}
}

renderpoints_s convert_3d_to_2d(point_s point, renderpoints_s renderpoint, float cam_dist) {
	renderpoint.x2d = point.x / (point.z/cam_dist + 1);
	renderpoint.y2d = point.y / (point.z/cam_dist + 1);
	return renderpoint;
}

GLFWwindow* OpenGLsetup() {
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(1000, 800, "3d Rotation Cube Simulation", NULL, NULL);
	glfwMakeContextCurrent(window);// toute les commands que je vais utilser de opengl font toucher cette fenetre
	glMatrixMode(GL_PROJECTION);// le type the mode a lequel on va voir la projection
    glLoadIdentity();// commence la simulation  sur une page vierge
    glOrtho(0, 1000, 800, 0, -1, 1);// limites de simulation display
	return window;
}

// OpenGL fais en sorte que quand tu met 2 points de suite que ca les connecte avec une ligne
void display_simulation(renderpoints_s* renders, GLFWwindow* window) {
	(void) window;
	// Draw cube edges
	glBegin(GL_LINES);
	// Front face
	glVertex2f(renders[0].x2d, renders[0].y2d); glVertex2f(renders[1].x2d, renders[1].y2d);
	glVertex2f(renders[1].x2d, renders[1].y2d); glVertex2f(renders[2].x2d, renders[2].y2d);
	glVertex2f(renders[2].x2d, renders[2].y2d); glVertex2f(renders[3].x2d, renders[3].y2d);
	glVertex2f(renders[3].x2d, renders[3].y2d); glVertex2f(renders[0].x2d, renders[0].y2d);
	// Back face
	glVertex2f(renders[4].x2d, renders[4].y2d); glVertex2f(renders[5].x2d, renders[5].y2d);
	glVertex2f(renders[5].x2d, renders[5].y2d); glVertex2f(renders[6].x2d, renders[6].y2d);
	glVertex2f(renders[6].x2d, renders[6].y2d); glVertex2f(renders[7].x2d, renders[7].y2d);
	glVertex2f(renders[7].x2d, renders[7].y2d); glVertex2f(renders[4].x2d, renders[4].y2d);
	// Sides
	glVertex2f(renders[0].x2d, renders[0].y2d); glVertex2f(renders[4].x2d, renders[4].y2d);
	glVertex2f(renders[1].x2d, renders[1].y2d); glVertex2f(renders[5].x2d, renders[5].y2d);
	glVertex2f(renders[2].x2d, renders[2].y2d); glVertex2f(renders[6].x2d, renders[6].y2d);
	glVertex2f(renders[3].x2d, renders[3].y2d); glVertex2f(renders[7].x2d, renders[7].y2d);
	glEnd();
}

int main()
{
	GLFWwindow *window;
	point_s points[8];
	point_s orig_points[8];
	renderpoints_s renders[8];
	float camera_distance = 1000;

	set_all_points(orig_points);

	window = OpenGLsetup();

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		for (int i = 0; i < 8; i++) {
            points[i] = orig_points[i];
        }
		rotate_all_points(points);
		for (int i = 0; i < 8; i++) {
			//convert_3d_to_2d(points[i], renders[i], camera_distance);

			//ca centre tout (chatgpt a fait ca)
			renders[i] = convert_3d_to_2d(points[i], renders[i], camera_distance);
			renders[i].x2d = renders[i].x2d * 20 + 500;
            renders[i].y2d = renders[i].y2d * 20 + 400;
		}
		display_simulation(renders, window);

		//printf("Point 0: (%.2f, %.2f, %.2f)\n", points[0].x, points[0].y, points[0].z);

		A += 0.008;
		B += 0.008;
		C += 0.008;

		glfwSwapBuffers(window); // affiche a l'ecran ce que je dessine
        glfwPollEvents(); // pour clavier souris (pour close)

		usleep(16000);// 60fps
	}

	glfwDestroyWindow(window);
    glfwTerminate();

	return 0;
}