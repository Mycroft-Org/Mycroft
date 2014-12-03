#include "Bullets.h"
#include <GL\glut.h>
#include <cstdlib>

Bullet::Bullet(float * eye, float * center)
{
	position[0] = eye[0] + (rand() % 11 - 5) * 0.01;
	position[1] = eye[1] + (rand() % 11 - 5) * 0.01;
	position[2] = eye[2] + (rand() % 11 - 5) * 0.01;

	direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];

	life = 100;
	alive = true;
	causedamage = false;
};

void Bullet::update()
{
	if (!alive)return;
	position[0] += direction[0] * speed;
	position[1] += direction[1] * speed;
	position[2] += direction[2] * speed;
	life--;
	if (life == 0)alive = false;
}
void Bullet::render()
{
	if (!alive)return;
	glPushMatrix();
	glTranslatef(position[0], position[1], position[2]);
	glutSolidCube(0.01);
	glPopMatrix();
}



Bullets::Bullets(float *eye, float *center) :eye(eye), center(center)
{
}

Bullets::~Bullets()
{
	active = false;
}

void Bullets::fire()
{
	active = true;
	counter =2;
	ware.clear();
	bulletWaiting = 0;
}

void Bullets::oneFrame()
{
	if (active) {
		if (bulletWaiting == 0) {
			bulletWaiting = bulletGap;
			Bullet bullet(eye, center);
			ware.push_back(bullet);
			counter--;
			if (counter == 0)
				active = false;
		}
		else {
			bulletWaiting--;
		}

	}
	for (auto it = ware.begin(); it != ware.end(); it++) {
		it->update();
	}
}
void Bullets::render()
{
	float bulletColor[] = { 1.0, 0.2, 0.2, 1.0 };
	float defaultColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, bulletColor);
	for (auto it = ware.begin(); it != ware.end(); it++) {
		it->render();
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT, defaultColor);
}