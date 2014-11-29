#ifndef _MOVER_H
#define _MOVER_H
#include <cmath>
class Mover
{
public:
	Mover(float * eye, float * center, float &lrRotate);
	~Mover();
	void zoomIn();
	void zoomOut();
	void turnLeft();
	void turnRight();
	void goUp();
	void goDown();
	void speedUp();
	void speedDown();
	float getMoveSpeed();
private:
	const float Pi = 3.14159265359;
	const float D = 3.0;
	float moveSpeed = 0.2f;
	float rotateSpeed = 3.0*Pi / 180;
	float &lrRotate;
	float *eye;
	float *center;
};


#endif