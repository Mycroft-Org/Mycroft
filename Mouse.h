#ifndef _MOUSE_H
#define _MOUSE_H
#include <cmath>
#include <GL/glut.h>
#include <windows.h>
class Mouse
{
public:
	Mouse(float * eye, float * center, float &lrRotate, float &udRotate, int &wHeight, int &wWidth, int &mouseX, int &mouseY);
	~Mouse();
	void  mouseMove_V1();
	void  mouseMove_V2();
private:
	const float Pi = 3.14159265359;
	const float D = 3.0;
	float udRotateLim = 30 * Pi / 180;
	float mouseRotateSpeed = 0.04*Pi / 180;
	float &lrRotate;
	float &udRotate;
	float *eye;
	float *center;
	int &wHeight , &wWidth;
	int &mouseX , &mouseY;
};


#endif