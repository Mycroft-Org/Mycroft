// glutEx1.cpp : 定义控制台应用程序的入口点。
//
//注意FPS函数的应用

#include <stdlib.h>
#include "glut.h" 
#include <stdio.h>
#include <string.h>
#include <math.h>
const float Pi = 3.14159265359;
float fTranslate;
float fRotate;
float fScale = 1.0f;	// set inital scale value to 1.0f
float fDistance = 0.2f;
float rotateEPS = 3.0*Pi / 180;
float lrRotate = -0.5*Pi;
float udRotate = 0;

float D = 3.0;
bool bPersp = false;
bool bAnim = false;
bool bWire = false;


int wHeight = 0;
int wWidth = 0;

void DrawWall();
void updateView(int width, int height)
{
	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	float whRatio = (GLfloat)width / (GLfloat)height;

	if (bPersp){
		gluPerspective(60, whRatio, 1, 100);
	}
	else
		glOrtho(-2 * whRatio, 2 * whRatio, -2, 2, -100, 100);
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

void reshape(int width, int height)
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	wHeight = height;
	wWidth = width;

	updateView(wWidth, wHeight);
}

void idle()
{
	glutPostRedisplay();
}

float eye[] = { 0, 0, 3 };
float center[] = { 0, 0, 0 };

void key(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 27:
	case 'q': {exit(0); break; }
	case 'p': {bPersp = !bPersp; updateView(wWidth, wHeight); break; }

	case ' ': {bAnim = !bAnim; break; }
	case 'o': {bWire = !bWire; break; }

	case 'j': {
		lrRotate = lrRotate - rotateEPS;
		center[0] = eye[0] + D*cos(lrRotate);
		center[2] = eye[2] + D*sin(lrRotate);
		break;
	}

	case 'l': {
		lrRotate = lrRotate + rotateEPS;
		center[0] = eye[0] + D*cos(lrRotate);
		center[2] = eye[2] + D*sin(lrRotate);
		break;
	}
	case 'z': {
		eye[0] = eye[0] + fDistance*cos(lrRotate);
		eye[2] = eye[2] + fDistance*sin(lrRotate);
		center[0] = center[0] + fDistance*cos(lrRotate);
		center[2] = center[2] + fDistance*sin(lrRotate);
		break;
	}
	case 'c': {
		eye[0] = eye[0] - fDistance*cos(lrRotate);
		eye[2] = eye[2] - fDistance*sin(lrRotate);
		center[0] = center[0] - fDistance*cos(lrRotate);
		center[2] = center[2] - fDistance*sin(lrRotate);
		break;
	}
	}
}
void draw()
{
	glutSolidCube(1);
}
void getFPS()
{
	static int frame = 0, time, timebase = 0;
	static char buffer[256];

	char mode[64];
	strcpy_s(mode, "naive");

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf_s(buffer, "FPS:%4.2f %s",
			frame*1000.0 / (time - timebase), mode);
		timebase = time;
		frame = 0;
	}

	char *c;
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);// 选择投影矩阵
	glPushMatrix();// 保存原矩阵
	glLoadIdentity();// 装入单位矩阵
	glOrtho(0, 480, 0, 480, -1, 1);// 位置正投影
	glMatrixMode(GL_MODELVIEW);// 选择Modelview矩阵
	glPushMatrix();// 保存原矩阵
	glLoadIdentity();// 装入单位矩阵*/
	glRasterPos2f(10, 10);
	for (c = buffer; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
	glMatrixMode(GL_PROJECTION);// 选择投影矩阵
	glPopMatrix();// 重置为原保存矩阵
	glMatrixMode(GL_MODELVIEW);// 选择Modelview矩阵
	glPopMatrix();// 重置为原保存矩阵
	glEnable(GL_DEPTH_TEST);
}

void redraw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);				// 场景（0，0，0）的视点中心 (0,5,50)，Y轴向上

	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_pos[] = { 5, 5, 5, 1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, white);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);



	glRotatef(fRotate, 0, 1.0f, 0);
	if (bAnim) fRotate += 0.5f;
	draw();


	//	Gen3DObjectList();


	if (bAnim) fRotate += 0.5f;

    DrawWall();

	getFPS();

	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480, 480);
	int windowHandle = glutCreateWindow("Simple GLUT App");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}
