#include "glut.h"
#include <stdio.h>
float wall_row[][3] = {
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
	{ 8, 0, 9 }
};

float wall_col[][3] = {
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
	{ 10, 0, 7 }
};

float wall_height = 1.0;
float wall_width = 0.06;
float amplifier = 10;
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

bool WallBlock(float x, float y, float z)
{
    x = x / amplifier;
    y = -y / amplifier;
	if (z>wall_height+10)
		return false;
    // Row Walls
    for (int i = 0; i < sizeof(wall_row) / sizeof(wall_row[0]); i++) {
        if (x >= wall_row[i][1] && x <= wall_row[i][2] && y >= wall_row[i][0] - wall_width / 2 && y <= wall_row[i][0] + wall_width / 2)
            return true;
    }

    // Column Walls
    for (int i = 0; i < sizeof(wall_col) / sizeof(wall_col[0]); i++) {
        if (y >= wall_col[i][1] && y <= wall_col[i][2] && x >= wall_col[i][0] - wall_width / 2 && x <= wall_col[i][0] + wall_width / 2)
            return true;
    }
    return false;
}

bool TeapotAttack(float x, float y)
{
    x = x / amplifier;
    y = -y / amplifier;
    if ((x>2.1) && (x<2.1) && (y>2.1) && (y<2.1))
        return true;
    return false;
}

void DrawTeapot(){
    glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, teapot_color);
   // glTranslatef(20, 15 ,1);
    glTranslatef(20, 20,0);
    glRotatef(90, 1, 0, 0);
    glScalef(3, 3, 3);
    glutSolidTeapot(1);
    glPopMatrix();

}
