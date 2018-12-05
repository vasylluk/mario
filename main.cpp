#include <GL/glut.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct type
{
    string name = "Block";
};

void resize(int w, int h)
{
	if (h == 0) h = 1;
	float ratio = w * 1.0 / h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, ratio, 0.1, 10);
	gluLookAt(0, 10, 4, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
}

vector<type> types;

void initTypes() {

	types.push_back(type());
}

int const short_x=2,short_y=3,short_z=2;
int const long_x=short_x*2+1, long_y=short_y+1, long_z=short_z*2+1;
int coord[long_x][long_y][long_z];

void initCoord(){
    for(int x=0;x<long_x;++x)
        for(int y=1;y<long_y;++y)
            for(int z=0;z<long_z;++z){
                coord[x][y][z]=0;
                }
    coord[0][3][0]= 1;
    coord[1][3][0]= 1;
    coord[2][3][0]= 1;
    coord[4][3][0]= 1;
    coord[1][2][1]= 1;
    coord[2][2][1]= 1;
    coord[3][2][1]= 1;
    coord[4][2][1]= 1;
    coord[0][3][1]= 1;
    coord[0][3][1]= 1;
    coord[0][3][1]= 1;
    coord[0][3][1]= 1;

}

float b_x=2,b_y=3,b_z=2, tap =0.1, r =0.5;
float cx=0.0, cy=0.0;
void display(void)
{   glColor3f(0.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(cx, 0.0, cy);
        glPushMatrix();
            for(int x=0;x<long_x;++x)
                for(int y=1;y<long_y;++y)
                    for(int z=0;z<long_z;++z){
                        if(coord[x][y][z] > 0){
                            glPushMatrix();
                                glTranslatef(x-short_x, y, z-short_z);
                                glutSolidCube(0.95);
                            glPopMatrix();
                            }
                        }
            glColor3f(1.0, 0.0, 0.0);
            glPushMatrix();
                glTranslated(b_x,b_y,b_z);
                glutSolidSphere(r,10,10);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
	glutSwapBuffers();
}
/*
bool crash(cube c) {
	if ((x1 - c.x)*(x1 - c.x) + (p_y1 - c.y)*(p_y1 - c.y) - (r1 + r2 / 2) > 0) {
		return false;
	}
	else {
		return true;
	}
}
*/
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a': b_x += (b_x - r - tap >= -short_x) ? -tap : 0; break;
	case 'd': b_x += (b_x + r + tap <= short_x) ? tap : 0; break;
	case 'w': b_z += (b_z + r + tap <= short_z) ? tap : 0; break;
	case 's': b_z += (b_z - r - tap >= -short_z) ? -tap : 0; break;
    case 'h': cx=cx+tap; break;
    case 'k': cx=cx-tap; break;
    case 'u': cy=cy+tap; break;
    case 'j': cy=cy-tap; break;

	}
	/*
	for (int i = 0; i < cubes.size(); i++) {
		cubes[i].crash = crash(cubes[i]) ? true : false;
	}
	*/
}

void arrow_keys(int keys, int x, int y) {
	switch (keys) {
	case GLUT_KEY_UP: glutFullScreen(); break;
	case GLUT_KEY_DOWN:glutReshapeWindow(800, 600); break;
	}
}

int main(int argc, char **argv) {
	initCoord();

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
