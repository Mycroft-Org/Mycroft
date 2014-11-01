#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include "glut.h" 
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
#define CONTROL 3
#define HELP 4
#define MAP_ON 5
#define MAP_CLOSE 6
extern float wall_row[][3];
extern float wall_col[][3];
const float Pi = 3.14159265359;
float fTranslate;
float fRotate;
float fScale = 1.0f;
float fDistance = 0.2f;
float rotateEPS = 3.0*Pi / 180;
float mouseRotateEPS = 0.04*Pi / 180;
float lrRotate = -0.5*Pi;
float udRotate = 0;
float udRotateLim = 30 * Pi / 180;
float D = 3.0;
float frameRate = 60;

bool mouseMode = true;
bool bPersp = true;
bool bAnim = false;
bool bWire = false;
bool bShow = false;
bool CURSOR = false;
bool wallTexture = false;
GLuint texGround,texwall;

int windowHandle, subwindowHandle;
int wHeight = 0;
int wWidth = 0;
int mouseX = 0, mouseY = 0;
int tips_count = 6;

GLuint load_texture(const char* file_name);
void ShowMap_Little();
void DrawWall();
void DrawTeapot();
bool WallBlock(float x, float y);
bool TeapotAttack(float x, float y);

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

float eye[] = { 0, 5, 3 };
float center[] = { 0, 5, 0 };

void key(unsigned char k, int x, int y)
{
	float eye0, eye2;
    switch (k) {
        case 27:
        case 'q': {exit(0); break; }
        case 'p': {bPersp = !bPersp; updateView(wWidth, wHeight); break; }
        //case ' ': {bAnim = !bAnim; break; }
        case 'o': {bWire = !bWire; break; }
		case 't': wallTexture = !wallTexture;
        case 'r': fDistance = fDistance*1.2; break;
        case 'f': fDistance = fDistance / 1.2; break;
		case 'm': 
			CURSOR = !CURSOR;
			ShowCursor(CURSOR);
			mouseMode = !mouseMode; 
			break; 
	
        case 'z':
            center[1] = center[1] + fDistance;
            eye[1] = eye[1] + fDistance;
            break;
        case 'c':
            center[1] = center[1] - fDistance;
            eye[1] = eye[1] - fDistance;
            break;
        case 'a':
            lrRotate = lrRotate - rotateEPS;
            center[0] = eye[0] + D*cos(lrRotate);
            center[2] = eye[2] + D*sin(lrRotate);
            break;
        case 'd':
            lrRotate = lrRotate + rotateEPS;
            center[0] = eye[0] + D*cos(lrRotate);
            center[2] = eye[2] + D*sin(lrRotate);
            break;

        case 'w':
            eye0 = eye[0] + fDistance*cos(lrRotate);
            eye2 = eye[2] + fDistance*sin(lrRotate);
            if (!WallBlock(eye0, eye2)) {
                eye[0] = eye0;
                eye[2] = eye2;
                center[0] = center[0] + fDistance*cos(lrRotate);
                center[2] = center[2] + fDistance*sin(lrRotate);
            }
            if (TeapotAttack(eye0, eye2)) {
                eye[0] -= 5 * fDistance*cos(lrRotate);
                eye[2] -= 5 * fDistance*sin(lrRotate);
            }
            break;
        case 's':
            eye0 = eye[0] - fDistance*cos(lrRotate);
            eye2 = eye[2] - fDistance*sin(lrRotate);
            if (!WallBlock(eye0, eye2)) {
                eye[0] = eye0;
                eye[2] = eye2;
                center[0] = center[0] - fDistance*cos(lrRotate);
                center[2] = center[2] - fDistance*sin(lrRotate);
            }
            break;
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
		sprintf_s(buffer, "FPS:%4.2f %s",
			frame*1000.0 / (time - timebase), mode);
		timebase = time;
		frame = 0;
	}

	char *c;
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
}
void mouseRotate_V1(){
	float lrSpeed = 0, udRadius = 0;
	static int time, timebase = 0;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase <= 4)  return;
	else timebase = time;
	if (mouseX < wWidth*0.45) lrSpeed = -3 * (wWidth*0.45 - mouseX) / (wWidth*0.45);
	else if (mouseX > wWidth*0.55) lrSpeed = 3 * (-wWidth*0.55 + mouseX) / (wWidth*0.45);
	else lrSpeed = 0;
	lrRotate = lrRotate + lrSpeed*mouseRotateEPS;
	center[0] = eye[0] + D*cos(lrRotate);
	center[2] = eye[2] + D*sin(lrRotate);
	if (mouseY < wHeight*0.40) udRadius = (+wHeight*0.40 - mouseY) / (wHeight*0.40);
	else if (mouseY > wHeight*0.60) udRadius = (+wHeight*0.60 - mouseY) / (wHeight*0.40);
	else udRadius = 0;
	center[1] = eye[1] + D*sin(udRotateLim*udRadius);
}
void mouseRotate_V2(){
	float lrSpeed = 0.1 * Pi / 180, udSpeed = -0.1 * Pi / 180;
	static int time, timebase = 0;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase <= 4)  return;
	else timebase = time;
	POINT p;
	GetCursorPos(&p);
	//printf("%ld %ld\n", p.x, p.y);
	mouseX = p.x;
	mouseY = p.y;
	//	printf("%ld %ld\n", mouseX, mouseY);
	//	printf("%d %.2lf %.2lf\n", mouseY, 1.0*wHeight / 2, wHeight*1.0 / 2);
	if (fabs((mouseX - 1.0*wWidth / 2) / (wWidth))>0.0)
	{
		lrRotate = lrRotate + (mouseX - wWidth*1.0 / 2)*lrSpeed;
		center[0] = eye[0] + D*cos(lrRotate);
		center[2] = eye[2] + D*sin(lrRotate);
	}
	if (fabs((mouseY - 1.0*wHeight / 2) / (wHeight)) > 0.0)
	{
		udRotate = udRotate + (mouseY - wHeight*1.0 / 2)*udSpeed;
		if (udRotate > udRotateLim) udRotate = udRotateLim;
		if (udRotate < -udRotateLim) udRotate = -udRotateLim;
		center[1] = eye[1] + D*sin(udRotate);
	}
	SetCursorPos(wWidth*1.0 / 2, wHeight*1.0 / 2);
	//	GetCursorPos(&p);
	//	printf("%ld %ld\n", p.x, p.y);


}
void textureGround()
{
	GLfloat ground_color[] = { 0.01, 0.01, 0.01, 1.0 };
	glBindTexture(GL_TEXTURE_2D, texGround);
	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ground_color);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 5.0f); glVertex3f(100.0f, 0.0f, 0.0f);
	glTexCoord2f(5.0f, 5.0f); glVertex3f(100.0f, 0.0f, -80.0f);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(0.0f, 0.0f, -80.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
void textureWall()
{
	glEnable(GL_TEXTURE_2D);
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
		glTexCoord2f(0.0f, 1.0f); glVertex3f(10 * wall_row[i][1] - 0.1f, 10.0f, -10 * wall_row[i][0] + 0.35f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(10 * wall_row[i][1] - 0.1f, 10.0f, -10 * wall_row[i][0] - 0.35f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(10 * wall_row[i][1] - 0.1f, 0.0f, -10 * wall_row[i][0] - 0.35f);

		glTexCoord2f(0.0f, 0.0f); glVertex3f(10 * wall_row[i][2] + 0.1f, 0.0f, -10 * wall_row[i][0] - 0.35f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(10 * wall_row[i][2] + 0.1f, 10.0f, -10 * wall_row[i][0] - 0.35f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(10 * wall_row[i][2] + 0.1f, 10.0f, -10 * wall_row[i][0] + 0.35f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(10 * wall_row[i][2] + 0.1f, 0.0f, -10 * wall_row[i][0] + 0.35f);
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
		glTexCoord2f(0.0f, 1.0f); glVertex3f(10 * wall_col[i][0] + 0.35f, 10.0f, -10 * wall_col[i][1] + 0.1f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(10 * wall_col[i][0] - 0.35f, 10.0f, -10 * wall_col[i][1] + 0.1f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(10 * wall_col[i][0] - 0.35f, 0.0f, -10 * wall_col[i][1] + 0.1f);

		glTexCoord2f(0.0f, 0.0f); glVertex3f(10 * wall_col[i][0] - 0.35f, 0.0f, -10 * wall_col[i][2] - 0.1f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(10 * wall_col[i][0] - 0.35f, 10.0f, -10 * wall_col[i][2] - 0.1f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(10 * wall_col[i][0] + 0.35f, 10.0f, -10 * wall_col[i][2] - 0.1f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(10 * wall_col[i][0] + 0.35f, 0.0f, -10 * wall_col[i][2] - 0.1f);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}
void redraw()
{
	if (mouseMode == true) mouseRotate_V2();
	else mouseRotate_V1();

	static int time, timebase = 0;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase <= 1000.0 / frameRate)  return;
	else timebase = time;


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

	GLfloat light_pos[] = { 0, 0, 10, 1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, white);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);glEnable(GL_TEXTURE_2D);
	textureGround();
	textureWall();
	draw();
	getFPS();
	glutSwapBuffers();
	/*glRotatef(fRotate, 0, 1.0f, 0);
	if (bAnim) fRotate += 0.5f;*/
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
	else{
		glutDestroyWindow(subwindowHandle);
		bShow = !bShow;
	}
}

void processMousePassiveMotion(int x, int y)
{
	/*	static int time, timebase = 0;
	double direction = 1.0;
	//time=*/
	mouseX = x;
	mouseY = y;
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
	case CONTROL:
		printf("hehehe\n"); break;
	case HELP:
		printf("cao\n"); break;
	}
}

void createGLUTMenus() {

	int menu;
	menu = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("TIPS/HIDE", MAP);
	glutAddMenuEntry("GRAPHYICS", GRAPHYICS);
	glutAddMenuEntry("CONTROL", CONTROL);
	glutAddMenuEntry("HELP", HELP);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
	ShowCursor(CURSOR);
	windowHandle = glutCreateWindow("Simple GLUT App");
	texGround = load_texture("2.bmp");
	printf("%d\n", texGround);
	texwall = load_texture("1.bmp");
	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);
	glutPassiveMotionFunc(processMousePassiveMotion);
	createGLUTMenus();
	glutMainLoop();
	return 0;
}