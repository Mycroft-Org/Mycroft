//#include "glut.h"
#include<GL/glut.h>
#include <stdio.h>
extern float eye[];
float wall_row[][3] = {
    { -1, -1, 11},
	{ 0, 1, 10 },
	{ 1, 1, 2 },
	{ 1, 9, 10 },
	{ 2, 0, 4 },
	{ 2, 5, 6 },
	{ 2, 7, 9 },
	{ 3, 1, 2 },
	{ 3, 6, 8 },
	{ 3, 9, 10 },
	{ 4, 2, 3 },
	{ 4, 5, 7 },
	{ 4, 8, 9 },
	{ 5, 3, 6 },
	{ 5, 7, 9 },
	{ 6, 0, 2 },
	{ 6, 4, 5 },
	{ 7, 1, 3 },
	{ 7, 5, 10 },
	{ 8, 0, 9 },
    { 9, -1, 11}
};

float wall_col[][3] = {
    { -1, -1, 9},
	{ 0, 1, 8 },
	{ 1, 3, 5 },
	{ 2, 0, 1 },
	{ 2, 2, 3 },
	{ 2, 4, 6 },
	{ 3, 1, 2 },
	{ 3, 3, 4 },
	{ 3, 5, 8 },
	{ 4, 1, 2 },
	{ 4, 3, 5 },
	{ 4, 6, 7 },
	{ 5, 0, 3 },
	{ 5, 6, 7 },
	{ 6, 4, 6 },
	{ 7, 1, 2 },
	{ 7, 3, 4 },
	{ 7, 5, 6 },
	{ 8, 0, 1 },
	{ 8, 2, 3 },
	{ 8, 4, 5 },
	{ 8, 6, 7 },
	{ 9, 3, 4 },
	{ 9, 5, 6 },
	{ 10, 0, 7 },
    { 11, -1, 9}
};

float wall_height = 1.0;
float wall_width = 0.06;
float wall_widthB = 0.08;
const float amplifier = 10;//in monster, too
GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_grey_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat mat_red_ambient[] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat mat_diffuse[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat no_shininess[] = { 0.0 };
GLfloat low_shininess[] = { 5.0 };
GLfloat high_shininess[] = { 100.0 };
GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };
GLfloat wall_color[] = { 0.1, 0.2, 0.2, 1.0 };
GLfloat teapot_color[] = { 0.2, 0.2, 0.2, 1.0 };

void DrawWall()
{
	float center_x, center_y, center_z;
	float scale_x, scale_y, scale_z;
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glMaterialfv(GL_FRONT, GL_AMBIENT, wall_color);
	//  glColorMaterial(GL_FRONT, GL_AMBIENT);
	//  glEnable(GL_COLOR_MATERIAL);

	// Row Walls
	center_z = wall_height / 2;
	scale_y = wall_width;
	scale_z = wall_height;
	for (int i = 0; i < sizeof(wall_row) / sizeof(wall_row[0]); i++) {
		center_x = (wall_row[i][1] + wall_row[i][2]) / 2;
		center_y = (wall_row[i][0]);
		scale_x = wall_row[i][2] - wall_row[i][1];
		glPushMatrix();
		//   glColor3fv(wall_color);
		glScalef(amplifier, amplifier, amplifier);
		glTranslatef(center_x, center_y, center_z);
		glScalef(scale_x, scale_y, scale_z);
		glutSolidCube(1.0);
		glPopMatrix();
	}

	// Column Walls
	center_z = wall_height / 2;
	scale_x = wall_width;
	scale_z = wall_height;
	for (int i = 0; i < sizeof(wall_col) / sizeof(wall_col[0]); i++) {
		center_y = (wall_col[i][1] + wall_col[i][2]) / 2;
		center_x = (wall_col[i][0]);
		scale_y = wall_col[i][2] - wall_col[i][1];
		glPushMatrix();
		glScalef(amplifier, amplifier, amplifier);
		glTranslatef(center_x, center_y, center_z);
		glScalef(scale_x, scale_y, scale_z);
		glutSolidCube(1.0);
		glPopMatrix();
	}
	//  glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

}

void ShowMap_Little()
{
	glColor3f(1.0f, 1.0f, 0.0f);
	GLfloat curSizeLine = 3;
	glLineWidth(curSizeLine);
	for (int i = 0; i < sizeof(wall_row) / sizeof(wall_row[0]); i++) {
		glBegin(GL_LINES);
		glVertex3f(wall_row[i][1] / 10, 0.0f, wall_row[i][0] / 10);
		glVertex3f(wall_row[i][2] / 10, 0.0f, wall_row[i][0] / 10);
		glEnd();
	}
	for (int i = 0; i < sizeof(wall_col) / sizeof(wall_col[0]); i++) {
		glBegin(GL_LINES);
		glVertex3f(wall_col[i][0] / 10, 0.0f, wall_col[i][1] / 10);
		glVertex3f(wall_col[i][0] / 10, 0.0f, wall_col[i][2] / 10);
		glEnd();
	}
}

int WallBlock(float x, float y, float z)
{
	x = x / amplifier;
	y = -y / amplifier;
	if (z>wall_height + 10)
		return 0;
	// Row Walls
	for (int i = 0; i < sizeof(wall_row) / sizeof(wall_row[0]); i++) {
		if (x >= wall_row[i][1] && x <= wall_row[i][2] && y >= wall_row[i][0] - wall_widthB / 2 && y <= wall_row[i][0] + wall_widthB / 2)
			return 1;
	}

	// Column Walls
	for (int i = 0; i < sizeof(wall_col) / sizeof(wall_col[0]); i++) {
		if (y >= wall_col[i][1] && y <= wall_col[i][2] && x >= wall_col[i][0] - wall_widthB / 2 && x <= wall_col[i][0] + wall_widthB / 2)
			return 2;
	}
	return 0;
}

void drawPos(float *eye)
{
	glColor3f(1.0f, 0.0f, 0.0f);
	GLfloat size = 10;
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex3f((eye[0]) / 50 - 1.0f, (3 - eye[2]) / 50 - 1.0f, 0.0f);
	glEnd();
}
void drawLittle()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);

	glTranslatef(-1.0f, 0.0f, -1.0f);
	glScalef(2.0f, 0.5f, 2.5f);
	ShowMap_Little();
	glPopMatrix();
	drawPos(eye);
	glutSwapBuffers();
}

