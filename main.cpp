#include <GL/glut.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct cube
{
	int x;
	int y;
    int z;
	bool crash;
};

void resize(int w, int h)
{
	if (h == 0) h = 1;
	float ratio = w * 1.0 / h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, ratio, 0.1, 10);
	gluLookAt(0, 2, 4, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
}

vector<cube> cubes;

void initCubes() {

	cubes.push_back(cube());
	cubes[0].x = 1.5;
	cubes[0].y = 1;
	cubes[0].z = 1;
	cubes[0].crash = false;

	cubes.push_back(cube());
	cubes[1].x = -1;
	cubes[1].y = 0.5;
	cubes[1].z = -1;
	cubes[1].crash = false;

	cubes.push_back(cube());
	cubes[2].x = -1;
	cubes[2].y = -1;
	cubes[2].z = 0;
	cubes[2].crash = false;

	cubes.push_back(cube());
	cubes[3].x = 1;
	cubes[3].y = 0;
	cubes[3].z = 1;
	cubes[3].crash = false;

	cubes.push_back(cube());
	cubes[4].x = 0;
	cubes[4].y = 0.5;
	cubes[4].z = 0.5;
	cubes[4].crash = false;

}

double x1 = 0, p_y1 = 0, r1 = 0.55, tap = 0.25, r2 = 0.5;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	for (int i = 0; i < cubes.size(); i++) {
		if (cubes[i].crash) {
			glColor3f(1.0, 1.0, 1.0);
		}
		else {
			glColor3f(1.0, 1.0, 0.0);
		}
		glPushMatrix();
		glTranslatef(cubes[i].x, cubes[i].y, cubes[i].z);
		glutSolidCube(r2);
		glPopMatrix();
	}
	glColor3f(0.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(x1, p_y1, 0);
	glutSolidSphere(r1, 100, 100);
	glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}

bool crash(cube c) {
	if ((x1 - c.x)*(x1 - c.x) + (p_y1 - c.y)*(p_y1 - c.y) - (r1 + r2 / 2) > 0) {
		return false;
	}
	else {
		return true;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a': x1 += (x1 - r1 - tap >= -3.5) ? -tap : 0; break;
	case 'd': x1 += (x1 + r1 + tap <= 3.5) ? tap : 0; break;
	case 'w': p_y1 += (p_y1 + r1 + tap <= 2) ? tap : 0; break;
	case 's': p_y1 += (p_y1 - r1 - tap >= -2) ? -tap : 0; break;

	}
	for (int i = 0; i < cubes.size(); i++) {
		cubes[i].crash = crash(cubes[i]) ? true : false;
	}
}

void arrow_keys(int keys, int x, int y) {
	switch (keys) {
	case GLUT_KEY_UP: glutFullScreen(); break;
	case GLUT_KEY_DOWN:glutReshapeWindow(800, 600); break;
	}
}

int main(int argc, char **argv) {
	initCubes();

	glutInit(&argc, argv);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(640, 480);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow("OpenGL1 Window");
	glutIdleFunc(display);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrow_keys);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glutMainLoop();
}
