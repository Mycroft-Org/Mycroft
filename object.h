#ifndef _OBJECT_H
#define _OBJECT_H
#include <cmath>
#include <gl/glut.h>
class Object{
public:
	int ground_texture;
	int wall_texture;
	Object();
	~Object();
	void textureSky();
	void textureWall();
	void textureGround();
private:
	GLuint texGround[3];
	GLuint texwall[3];
	GLuint texSky;

};

#endif