#include "Mouse.h"

Mouse::Mouse(float * eye, float * center, float &lrRotate, float &udRotate, int &wHeight, int &wWidth, int &mouseX, int &mouseY)
	:eye(eye), center(center), lrRotate(lrRotate), udRotate(udRotate), wHeight(wHeight), wWidth(wWidth), mouseX(mouseX), mouseY(mouseY){
}

void Mouse::mouseMove_V1(){
	float lrSpeed = 0, udRadius = 0;
	static int time, timebase = 0;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase <= 4)  return;
	else timebase = time;
	if (mouseX < wWidth*0.45) lrSpeed = -3 * (wWidth*0.45 - mouseX) / (wWidth*0.45);
	else if (mouseX > wWidth*0.55) lrSpeed = 3 * (-wWidth*0.55 + mouseX) / (wWidth*0.45);
	else lrSpeed = 0;
	lrRotate = lrRotate + lrSpeed*mouseRotateSpeed;
	center[0] = eye[0] + D*cos(lrRotate);
	center[2] = eye[2] + D*sin(lrRotate);
	if (mouseY < wHeight*0.40) udRadius = (+wHeight*0.40 - mouseY) / (wHeight*0.40);
	else if (mouseY > wHeight*0.60) udRadius = (+wHeight*0.60 - mouseY) / (wHeight*0.40);
	else udRadius = 0;
	center[1] = eye[1] + D*sin(udRotateLim*udRadius);
}

void Mouse::mouseMove_V2(){
	float lrSpeed = 0.1 * Pi / 180, udSpeed = -0.1 * Pi / 180;
	static int time, timebase = 0;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase <= 4)  return;
	else timebase = time;
	POINT p;
	GetCursorPos(&p);
	mouseX = p.x;
	mouseY = p.y;
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
}