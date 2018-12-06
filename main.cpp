#include <GL/glut.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

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

struct object
{
	int x;
	int y;
    int z;
};

vector<object> objects;

void initObjects() {
 	objects.push_back(object());
	objects[objects.size()-1].x = 1;
	objects[objects.size()-1].y = 3;
	objects[objects.size()-1].z = 1;
 	objects.push_back(object());
	objects[objects.size()-1].x = -1;
	objects[objects.size()-1].y = 3;
	objects[objects.size()-1].z = -1;
 	objects.push_back(object());
	objects[objects.size()-1].x = -1;
	objects[objects.size()-1].y = 3;
	objects[objects.size()-1].z = 0;
 	objects.push_back(object());
	objects[objects.size()-1].x = 1;
	objects[objects.size()-1].y = 3;
	objects[objects.size()-1].z = 1;
 	objects.push_back(object());
	objects[objects.size()-1].x = 0;
	objects[objects.size()-1].y = 3;
	objects[objects.size()-1].z = 1;
 }


struct type
{
    string name = "Block";
};


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
    coord[1][2][2]= 1;
    coord[2][2][2]= 1;
    coord[3][2][2]= 1;
    coord[4][2][2]= 1;
    coord[1][2][3]= 1;
    coord[2][2][3]= 1;
    coord[3][2][3]= 1;
    coord[4][2][3]= 1;
    coord[1][2][4]= 1;
    coord[2][2][4]= 1;
    coord[3][2][4]= 1;
    coord[4][2][4]= 1;
    coord[0][2][1]= 1;

}

float b_x=2,b_y=3,b_z=2, tap =0.1, r =0.5;
float cx=0.0, cy=0.0;
int sing=0;
void display(void)
{   glColor3f(0.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glRotated(sing,0,1,0);
	glTranslatef(cx, 0.0, cy);
    glPushMatrix();
        for(int x=0;x<long_x;++x){
            for(int y=1;y<long_y;++y){
                for(int z=0;z<long_z;++z){
                    if(coord[x][y][z] > 0){
                        glPushMatrix();
                            glTranslatef(x-short_x, y, z-short_z);
                            glutSolidCube(0.95);
                        glPopMatrix();
                    }
                }
            }
        }
        glColor3f(0.0, 0.0, 1.0);
        for (int i = 0; i < objects.size(); i++) {
            glPushMatrix();
                glTranslatef(objects[i].x, objects[i].y, objects[i].z);
                glutSolidCube(0.5);
            glPopMatrix();
        }
        glColor3f(1.0, 0.0, 0.0);
        glPushMatrix();
            glTranslated(b_x,b_y,b_z);
            glutSolidSphere(r,10,10);
        glPopMatrix();
    glPopMatrix();
	glutSwapBuffers();
	if(coord[(int)b_x-short_x][(int)(b_y-tap)][(int)b_z-short_z]==0){
	b_y-=tap/10;
	/*
	cout<<"x="<<(int)b_x<<"("<<b_x<<")  ";
	cout<<"y="<<(int)b_y<<"("<<b_y<<")  ";
	cout<<"z="<<(int)b_z<<"("<<b_z<<")  ";
	*/
	}
}

void go(){
    switch(sing){
    case 270: b_x-= (b_x - r - tap >= -short_x) ? tap : 0; break;
    case 180: b_z+= (b_z + r + tap <=  short_z) ? tap : 0; break;
    case 90 : b_x+= (b_x + r + tap <=  short_x) ? tap : 0; break;
    case 0  : b_z-= (b_z - r - tap >= -short_z) ? tap : 0; break;
    }
}

bool crash(object c) {
	if ((b_x - c.x)*(b_x - c.x) + (b_y - c.y)*(b_y - c.y) - ((r +1) / 2) > 0) {
		return false;
	}
	else {
		return true;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a': sing-= 90; if(sing<0) sing =360; break;
	case 'd': sing+= 90; if(sing>=360) sing =0; break;
	case 'w': {go(); break;}
	case ' ': b_y+=2;
    case 'h': cx=cx+tap; break;
    case 'k': cx=cx-tap; break;
    case 'u': cy=cy+tap; break;
    case 'j': cy=cy-tap; break;
	}
    for (int i = 0; i < objects.size(); i++) {
        if(crash(objects[i])){
            objects.erase(objects.begin()+i);
        }
	}
	if(objects.size()==0){exit(0);}
}

void arrow_keys(int keys, int x, int y) {
	switch (keys) {
	case GLUT_KEY_UP: glutFullScreen(); break;
	case GLUT_KEY_DOWN:glutReshapeWindow(800, 600); break;
	}
}

int main(int argc, char **argv) {
	initCoord();
	initObjects();

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
