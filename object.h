#ifndef _OBJECT_H
#define _OBJECT_H
#include <cmath>
#include <gl/glut.h>
#include "glm.h"
class Object{
public:
	int ground_texture;
	int wall_texture;
	Object(int &wWidth, int &wHeight, float &lrRotate);
	~Object();
	void textureSky();
	void textureWall();
	void textureGround();
	void drawFlag();
	void drawCompass();
private:
	GLuint texGround[3];
	GLuint texwall[3];
	GLuint texSky;
	GLMmodel  *pFlag;
	int &wWidth,&wHeight;
	float &lrRotate;
};

#endif