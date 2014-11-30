#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include<sstream>   


using  namespace std;
//#include "glut.h" 
#include<GL/glut.h>
#include "Jumper.h"
#include "Move.h"
#include "Mouse.h"
#include "glm.h"
/*Simple HELP
A:Turn left
D:Turn right
W:Move forward
S:Move backward
Z:Move upward
C:Move downward
*/

#define MAP 1
#define GRAPHYICS 2
#define COPY 3
#define HELP 4
#define MAP_ON 5
#define MAP_CLOSE 6
#define WindowHeight 600
#define  WindowWidth 800

extern float wall_row[][3];
extern float wall_col[][3];
const float D = 3.0;
const float Pi = 3.14159265359;
float fTranslate;
float fRotate;
float fScale = 1.0f;

float lrRotate = -0.5*Pi;
float udRotate = 0;


float frameRate = 60;

bool mouseMode = true;
bool bPersp = true;
bool bAnim = false;
bool bWire = false;
bool bShow = false;
bool bSpotLight = false;
bool bPointer = false;
bool CURSOR = false;
bool wallTexture = false;
GLuint texGround, texwall;
GLMmodel *pWomen,*pEight;
int windowHandle, subwindowHandle, windowHandle2, subwindowHandle2;
int wHeight = 0, wWidth = 0;
int mouseX = 0, mouseY = 0;
int tips_count = 6;

GLuint load_texture(const char* file_name);
void ShowMap_Little();
void DrawWall();
void DrawTeapot();
bool WallBlock(float x, float y, float z);
bool TeapotAttack(float x, float y);
void redraw_pointer();

Jumper * pJumper;
Mover *pMover;
Mouse *pMouse;
void updateView(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float whRatio = (GLfloat)width / (GLfloat)height;

	if (bPersp){
		gluPerspective(30, whRatio, 0.1, 100);
	}
	else
		glOrtho(-2 * whRatio, 2 * whRatio, -2, 2, -100, 100);
	glMatrixMode(GL_MODELVIEW);
}

void reshape(int width, int height)
{
	if (height == 0)
	{
		height = 1;
	}

	wHeight = height;
	wWidth = width;

	updateView(wWidth, wHeight);
}

void idle()
{
	glutPostRedisplay();
}

float eye[] = { 0, 5, 0+D ,1};
float center[] = { 0, 5, 0 };

void key(unsigned char k, int x, int y)
{
	switch (k) {
	case 27:
	case 'q': exit(0); break; 
	case 'p': bPersp = !bPersp; updateView(wWidth, wHeight); break; 
	case 'o': bWire = !bWire;             break; 
	case 'l': bSpotLight = !bSpotLight;   break;
	case 't': wallTexture = !wallTexture; break;
	case 'm': CURSOR = !CURSOR;	ShowCursor(CURSOR);	mouseMode = !mouseMode;	break;
	case 'r':pMover->speedUp();     break;
	case 'f':pMover->speedDown();   break;
	case 'z':pMover->goUp();		    break;
	case 'c':pMover->goDown();		break;
	case 'a':pMover->turnLeft();		break;
	case 'd':pMover->turnRight();	break;
	case 'w':pMover->zoomIn();		break;
	case 's':pMover->zoomOut();		break;
    case ' ':pJumper->jump();       break;
	}

}
void draw()
{
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	DrawWall();
	DrawTeapot();
	glPopMatrix();
}
void drawPos()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	GLfloat size = 10;
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex3f((eye[0]) / 50 - 1.0f, (3 - eye[2]) / 50 - 1.0f, 0.0f);
	glEnd();
}


void getFPS()
{
	GLfloat White[] = { 1.0, 1.0, 1.0, 1.0 };

	static int frame = 0, time, timebase = 0;
	static char buffer[256];
	char mode[64];
	strcpy_s(mode, "naive");

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf_s(buffer, "FPS:%4.2f %s  Speed:%.2f",
			frame*1000.0 / (time - timebase), mode, pMover->getMoveSpeed());
		timebase = time;
		frame = 0;
	}

	char *c;
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 480, 0, 480, -1, 1);
	glMaterialfv(GL_FRONT, GL_AMBIENT, White);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2f(10, 10);
	for (c = buffer; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}


void textureGround()
{
	glEnable(GL_TEXTURE_2D);
	GLfloat ground_color[] = { 0.01, 0.01, 0.01, 1.0 };
	glBindTexture(GL_TEXTURE_2D, texGround);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBegin(GL_QUADS);
	//glMaterialfv(GL_FRONT, GL_AMBIENT, ground_color);
	double dl = 100.0;
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-500.0f, 0.0f, -500.0f);
	glTexCoord2f(dl, 0.0f); glVertex3f(500.0f, 0.0f, -500.0f);
	glTexCoord2f(dl, dl); glVertex3f(500.0f, 0.0f, 500.0f);
	glTexCoord2f(0.0f, dl); glVertex3f(-500.0f, 0.0f, 500.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
void textureWall()
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	if (!wallTexture)	glBindTexture(GL_TEXTURE_2D, texwall);
	else	glBindTexture(GL_TEXTURE_2D, texGround);
	for (int i = 0; i < 19; i++) {

		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f); glVertex3f(10 * wall_row[i][1] - 0.1f, 0.0f, -10 * wall_row[i][0] + 0.35f);
		glTexCoord2f(0.0f, 5.0f); glVertex3f(10 * wall_row[i][1] - 0.1f, 10.0f, -10 * wall_row[i][0] + 0.35f);
		glTexCoord2f(5.0f*fabs(wall_row[i][2] - wall_row[i][1]), 5.0f); glVertex3f(10 * wall_row[i][2] + 0.1f, 10.0f, -10 * wall_row[i][0] + 0.35f);
		glTexCoord2f(5.0f*fabs(wall_row[i][2] - wall_row[i][1]), 0.0f); glVertex3f(10 * wall_row[i][2] + 0.1f, 0.0f, -10 * wall_row[i][0] + 0.35f);

		glTexCoord2f(0.0f, 0.0f); glVertex3f(10 * wall_row[i][1] - 0.1f, 0.0f, -10 * wall_row[i][0] - 0.35f);
		glTexCoord2f(0.0f, 5.0f); glVertex3f(10 * wall_row[i][1] - 0.1f, 10.0f, -10 * wall_row[i][0] - 0.35f);
		glTexCoord2f(5.0f*fabs(wall_row[i][2] - wall_row[i][1]), 5.0f); glVertex3f(10 * wall_row[i][2] + 0.1f, 10.0f, -10 * wall_row[i][0] - 0.35f);
		glTexCoord2f(5.0f*fabs(wall_row[i][2] - wall_row[i][1]), 0.0f); glVertex3f(10 * wall_row[i][2] + 0.1f, 0.0f, -10 * wall_row[i][0] - 0.35f);

		glTexCoord2f(0.0f, 0.0f); glVertex3f(10 * wall_row[i][1] - 0.1f, 0.0f, -10 * wall_row[i][0] + 0.35f);
		glTexCoord2f(0.0f, 5.0f); glVertex3f(10 * wall_row[i][1] - 0.1f, 10.0f, -10 * wall_row[i][0] + 0.35f);
		glTexCoord2f(0.7 / 2.0f, 5.0f); glVertex3f(10 * wall_row[i][1] - 0.1f, 10.0f, -10 * wall_row[i][0] - 0.35f);
		glTexCoord2f(0.7 / 2.0f, 0.0f); glVertex3f(10 * wall_row[i][1] - 0.1f, 0.0f, -10 * wall_row[i][0] - 0.35f);

		glTexCoord2f(0.0f, 0.0f); glVertex3f(10 * wall_row[i][2] + 0.1f, 0.0f, -10 * wall_row[i][0] - 0.35f);
		glTexCoord2f(0.0f, 5.0f); glVertex3f(10 * wall_row[i][2] + 0.1f, 10.0f, -10 * wall_row[i][0] - 0.35f);
		glTexCoord2f(0.7 / 2.0f, 5.0f); glVertex3f(10 * wall_row[i][2] + 0.1f, 10.0f, -10 * wall_row[i][0] + 0.35f);
		glTexCoord2f(0.7 / 2.0f, 0.0f); glVertex3f(10 * wall_row[i][2] + 0.1f, 0.0f, -10 * wall_row[i][0] + 0.35f);
		glEnd();
	}
	for (int i = 0; i < 24; i++) {

		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f); glVertex3f(10 * wall_col[i][0] + 0.35f, 0.0f, -10 * wall_col[i][1] + 0.1f);
		glTexCoord2f(0.0f, 5.0f); glVertex3f(10 * wall_col[i][0] + 0.35f, 10.0f, -10 * wall_col[i][1] + 0.1f);
		glTexCoord2f(5.0f*fabs(wall_col[i][2] - wall_col[i][1]), 5.0f); glVertex3f(10 * wall_col[i][0] + 0.35f, 10.0f, -10 * wall_col[i][2] - 0.1f);
		glTexCoord2f(5.0f*fabs(wall_col[i][2] - wall_col[i][1]), 0.0f); glVertex3f(10 * wall_col[i][0] + 0.35f, 0.0f, -10 * wall_col[i][2] - 0.1f);

		glTexCoord2f(0.0f, 0.0f); glVertex3f(10 * wall_col[i][0] - 0.35f, 0.0f, -10 * wall_col[i][1] + 0.1f);
		glTexCoord2f(0.0f, 5.0f); glVertex3f(10 * wall_col[i][0] - 0.35f, 10.0f, -10 * wall_col[i][1] + 0.1f);
		glTexCoord2f(5.0f*fabs(wall_col[i][2] - wall_col[i][1]), 5.0f); glVertex3f(10 * wall_col[i][0] - 0.35f, 10.0f, -10 * wall_col[i][2] - 0.1f);
		glTexCoord2f(5.0f*fabs(wall_col[i][2] - wall_col[i][1]), 0.0f); glVertex3f(10 * wall_col[i][0] - 0.35f, 0.0f, -10 * wall_col[i][2] - 0.1f);

		glTexCoord2f(0.0f, 0.0f); glVertex3f(10 * wall_col[i][0] + 0.35f, 0.0f, -10 * wall_col[i][1] + 0.1f);
		glTexCoord2f(0.0f, 5.0f); glVertex3f(10 * wall_col[i][0] + 0.35f, 10.0f, -10 * wall_col[i][1] + 0.1f);
		glTexCoord2f(0.7 / 2.0f, 5.0f); glVertex3f(10 * wall_col[i][0] - 0.35f, 10.0f, -10 * wall_col[i][1] + 0.1f);
		glTexCoord2f(0.7 / 2.0f, 0.0f); glVertex3f(10 * wall_col[i][0] - 0.35f, 0.0f, -10 * wall_col[i][1] + 0.1f);

		glTexCoord2f(0.0f, 0.0f); glVertex3f(10 * wall_col[i][0] - 0.35f, 0.0f, -10 * wall_col[i][2] - 0.1f);
		glTexCoord2f(0.0f, 5.0f); glVertex3f(10 * wall_col[i][0] - 0.35f, 10.0f, -10 * wall_col[i][2] - 0.1f);
		glTexCoord2f(0.7 / 2.0f, 5.0f); glVertex3f(10 * wall_col[i][0] + 0.35f, 10.0f, -10 * wall_col[i][2] - 0.1f);
		glTexCoord2f(0.7 / 2.0f, 0.0f); glVertex3f(10 * wall_col[i][0] + 0.35f, 0.0f, -10 * wall_col[i][2] - 0.1f);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}
void draw_solid_circle(float x, float y, float radius)
{
	int count;
	int sections = 200;

	GLfloat TWOPI = 2.0f * 3.14159f;

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x, y, 0);

	for (count = 0; count <= sections; count++)
	{
		glVertex2f(x + radius*cos(count*TWOPI / sections), y + radius*sin(count*TWOPI / sections));
	}
	glEnd();
}
void drawCompass(){
	GLfloat White[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat Black[] = { 0.0, 0.0, 0.0, 1.0 };
	int n = 360;
	float R = 50, r = 10;
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 480 * wWidth / wHeight, 0, 480, -1000, 1000);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMaterialfv(GL_FRONT, GL_AMBIENT, Black);
	draw_solid_circle(R + 15, 100, R);
	glMaterialfv(GL_FRONT, GL_AMBIENT, White);
	draw_solid_circle(65 + cos(-lrRotate)*(R - r - 5), 100 + sin(-lrRotate)*(R - r - 5), r);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
}
void redraw()
{ 
	static int time, timebase = 0;
	mouseMode ? pMouse->mouseMove_V2() : pMouse->mouseMove_V1();

	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase <= 1000.0 / frameRate)  return;
		else timebase = time;

    pJumper->oneFrame();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);

	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat dark[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat grey[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat mid[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat blue[] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat light_pos[] = { 0, 1, 1, 0 };
	GLfloat light_dir[4] = { 0.0, 0.0, 0.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);	
	glLightfv(GL_LIGHT0, GL_AMBIENT, mid);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);	
	for (int i = 0; i < 3; i++)
		light_dir[i] = center[i] - eye[i];
	glLightfv(GL_LIGHT1, GL_POSITION, eye);
	glLightfv(GL_LIGHT1, GL_AMBIENT, blue);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, blue);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 15);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_dir);
	glLightf(GL_LIGHT1 ,GL_SPOT_EXPONENT, 2.);
	glEnable(GL_LIGHT0); 
	bSpotLight ? glEnable(GL_LIGHT1) : glDisable(GL_LIGHT1);
	textureGround();
	textureWall();
	//draw();
	drawCompass();
	getFPS();
	//glutSolidSphere(0.1, 20, 20);
	/*women1
	glTranslatef(0, 3.0, 0);
	glScalef(0.004, 0.004, 0.004);
	glmDraw(pModel, GLM_SMOOTH);*/
	glTranslatef(0, 2, 0);
	glScalef(0.05, 0.05, 0.05);
	glmDraw(pEight, GLM_SMOOTH);
	glutSwapBuffers();
}

void redraw_little()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);

	glTranslatef(-1.0f, 0.0f, -1.0f);
	glScalef(2.0f, 0.5f, 2.5f);
	ShowMap_Little();
	glPopMatrix();
	drawPos();
	glutSwapBuffers();
}



void create_subwindow()
{
	if (!bShow){
		subwindowHandle = glutCreateSubWindow(windowHandle, 0, 0, 200, 100);
		glutDisplayFunc(redraw_little);
		glutIdleFunc(idle);
		bShow = !bShow;
	}
	/*else{
	glutDestroyWindow(subwindowHandle);
	bShow = !bShow;
	}*/
}

void processMousePassiveMotion(int x, int y)
{
	mouseX = x;
	mouseY = y;
}

void grab(void)
{
	FILE* pDummyFile;
	FILE* pWritingFile;
	GLubyte* pPixelData;
	GLubyte BMP_Header[54];
	GLint i, j;
	GLint PixelDataLength;
	
	i = WindowWidth * 3; 
	while (i % 4 != 0) 
		++i;
	PixelDataLength = i * WindowHeight;
	pPixelData = (GLubyte*)malloc(PixelDataLength);
	if (pPixelData == 0)
		exit(0);
	fopen_s(&pDummyFile,"1.bmp", "rb");
	if (pDummyFile == 0)
		exit(0);
	fopen_s(&pWritingFile,"grab.bmp", "wb");
	if (pWritingFile == 0)
		exit(0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glReadPixels(0, 0, WindowWidth, WindowHeight,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pPixelData);
	fread(BMP_Header, sizeof(BMP_Header), 1, pDummyFile);
	fwrite(BMP_Header, sizeof(BMP_Header), 1, pWritingFile);
	fseek(pWritingFile, 0x0012, SEEK_SET);
	i = WindowWidth;
	j = WindowHeight;
	fwrite(&i, sizeof(i), 1, pWritingFile);
	fwrite(&j, sizeof(j), 1, pWritingFile);
	fseek(pWritingFile, 0, SEEK_END);
	fwrite(pPixelData, PixelDataLength, 1, pWritingFile);
	fclose(pDummyFile);
	fclose(pWritingFile);
	free(pPixelData);
}



void processMenuEvents(int option) {
	switch (option) {
	case MAP:
		if (tips_count > 0){
			create_subwindow();
			tips_count--;
		}
		else
			;
		break;
	case GRAPHYICS:
		printf("hehe\n"); break;
	case COPY:
		grab();
		break;
	case HELP:
		printf("cao\n"); break;
	}
}

void createGLUTMenus() {

	int menu;
	menu = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("TIPS/HIDE", MAP);
	glutAddMenuEntry("GRAPHYICS", GRAPHYICS);
	glutAddMenuEntry("COPY", COPY);
	glutAddMenuEntry("HELP", HELP);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

int main(int argc, char *argv[])
{
    pJumper = new Jumper(eye[1], center[1]);
	pMover = new Mover(eye, center,lrRotate);
	pMouse = new Mouse(eye, center, lrRotate, udRotate, wHeight, wWidth, mouseX, mouseY);
	pEight = glmReadOBJ("eight.obj");
	//pWomen = glmReadOBJ("women.obj");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
	ShowCursor(CURSOR);
	windowHandle = glutCreateWindow("Simple GLUT App");
	texGround = load_texture("ground_1.bmp");
	texwall = load_texture("wall_1.bmp");
	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);
	glutPassiveMotionFunc(processMousePassiveMotion);
	createGLUTMenus();
	glutMainLoop();
	return 0;
}