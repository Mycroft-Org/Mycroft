#include "object.h"
#include <stdio.h>
GLuint load_texture(const char* file_name);
float wall_row[][3];
float wall_col[][3];
Object::Object(int &wWidth, int &wHeight, float &lrRotate) :wWidth(wWidth), wHeight(wHeight), lrRotate(lrRotate){
	ground_texture = 0;
	wall_texture = 0;
	texGround[0] = load_texture("ground_0.bmp");
	texGround[1] = load_texture("ground_1.bmp");
	texGround[2] = load_texture("ground_2.bmp");

	texwall[0] = load_texture("wall_0.bmp");
	texwall[1] = load_texture("wall_1.bmp");
	texwall[2] = load_texture("wall_2.bmp");
	texSky = load_texture("sky_2.bmp");

	pFlag = glmReadOBJ("flag.obj");
}

void Object::textureSky()
{
	float A = 100, Mx = 50, Mz = -40, Time = 2.0;
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texSky);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(Mx - A, 0, Mz - A);		glTexCoord2f(0.0f, Time); glVertex3f(Mx - A, A, Mz - A);
	glTexCoord2f(Time, Time); glVertex3f(Mx - A, A, Mz + A);		glTexCoord2f(Time, 0.0f); glVertex3f(Mx - A, 0, Mz + A);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(Mx - A, 0, Mz - A);		glTexCoord2f(0.0f, Time); glVertex3f(Mx - A, A, Mz - A);
	glTexCoord2f(Time, Time); glVertex3f(Mx + A, A, Mz - A);		glTexCoord2f(Time, 0.0f); glVertex3f(Mx + A, 0, Mz - A);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(Mx + A, 0, Mz - A);		glTexCoord2f(0.0f, Time); glVertex3f(Mx + A, A, Mz - A);
	glTexCoord2f(Time, Time); glVertex3f(Mx + A, A, Mz + A);		glTexCoord2f(Time, 0.0f); glVertex3f(Mx + A, 0, Mz + A);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(Mx - A, 0, Mz + A);		glTexCoord2f(0.0f, Time); glVertex3f(Mx - A, A, Mz + A);
	glTexCoord2f(Time, Time); glVertex3f(Mx + A, A, Mz + A);		glTexCoord2f(Time, 0.0f); glVertex3f(Mx + A, 0, Mz + A);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(Mx - A, A, Mz - A);		glTexCoord2f(0.0f, Time); glVertex3f(Mx - A, A, Mz + A);
	glTexCoord2f(Time, Time); glVertex3f(Mx + A, A, Mz + A);		glTexCoord2f(Time, 0.0f); glVertex3f(Mx + A, A, Mz - A);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
void Object::textureGround()
{
	glEnable(GL_TEXTURE_2D);
	GLfloat ground_color[] = { 0.01, 0.01, 0.01, 1.0 };
	glBindTexture(GL_TEXTURE_2D, texGround[ground_texture]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBegin(GL_QUADS);
	double dl = 100.0;
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-500.0f, 0.0f, -500.0f);
	glTexCoord2f(dl, 0.0f); glVertex3f(500.0f, 0.0f, -500.0f);
	glTexCoord2f(dl, dl); glVertex3f(500.0f, 0.0f, 500.0f);
	glTexCoord2f(0.0f, dl); glVertex3f(-500.0f, 0.0f, 500.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
void Object::textureWall()
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texwall[wall_texture]);
	for (int i = 0; i < 21; i++) {

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
	for (int i = 0; i < 26; i++) {

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

void Object::drawFlag(){
	glPushMatrix();
	glTranslatef(105, 0, -75);
	glRotated(90, 0, 1, 0);
	glScalef(0.001, 0.001, 0.001);
	glmDraw(pFlag, GLM_SMOOTH);
	glPopMatrix();
}
void drawSolidCircle(float x, float y, float radius)
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
void Object::drawCompass(){
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
	drawSolidCircle(R + 15, 100, R);
	glMaterialfv(GL_FRONT, GL_AMBIENT, White);
	drawSolidCircle(65 + cos(-lrRotate)*(R - r - 5), 100 + sin(-lrRotate)*(R - r - 5), r);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
}

