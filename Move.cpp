#include "Move.h"
int WallBlock(float x, float y, float z);
Mover::Mover(float * eye, float * center, float &lrRotate) :eye(eye), center(center), lrRotate(lrRotate){
}

void Mover::zoomIn(){
	float eye0, eye2,eye01,eye21;
	eye0 = eye[0] + moveSpeed*cos(lrRotate);
	eye2 = eye[2] + moveSpeed*sin(lrRotate);
	eye01 = eye0 + moveSpeed*cos(lrRotate);
	eye21 = eye2 + moveSpeed*sin(lrRotate);
	if (!WallBlock(eye0, eye2, eye[1])) {
		eye[0] = eye0;
		eye[2] = eye2;
		center[0] = center[0] + moveSpeed*cos(lrRotate);
		center[2] = center[2] + moveSpeed*sin(lrRotate);
	}
	else if (WallBlock(eye0, eye2, eye[1]) == 1){
		if (WallBlock(eye01, eye2, eye[1]) == 2)
			eye[0] = eye[0];
		else
		{
			eye[0] = eye0;
			center[0] = center[0] + moveSpeed*cos(lrRotate);
		}
	}
	else if (WallBlock(eye0, eye2, eye[1] == 2)){
		if (WallBlock(eye0, eye21, eye[1]) == 1)
			eye[2] = eye[2];
		else
		{
			eye[2] = eye2;
			center[2] = center[2] + moveSpeed*sin(lrRotate);
		}
	}

}

void Mover::zoomOut(){
	float eye0, eye2;
	eye0 = eye[0] - moveSpeed*cos(lrRotate);
	eye2 = eye[2] - moveSpeed*sin(lrRotate);
	if (!WallBlock(eye0, eye2, eye[1])) {
		eye[0] = eye0;
		eye[2] = eye2;
		center[0] = center[0] - moveSpeed*cos(lrRotate);
		center[2] = center[2] - moveSpeed*sin(lrRotate);
	}
	else if (WallBlock(eye0, eye2, eye[1]) == 1){
		eye[0] = eye0;
		center[0] = center[0] - moveSpeed*cos(lrRotate);
	}
	else if (WallBlock(eye0, eye2, eye[1] == 2)){
		eye[2] = eye2;
		center[2] = center[2] - moveSpeed*sin(lrRotate);
	}
}
void Mover::turnLeft(){
	lrRotate = lrRotate - rotateSpeed;
	center[0] = eye[0] + D*cos(lrRotate);
	center[2] = eye[2] + D*sin(lrRotate);
}
void Mover::turnRight(){
	lrRotate = lrRotate + rotateSpeed;
	center[0] = eye[0] + D*cos(lrRotate);
	center[2] = eye[2] + D*sin(lrRotate);
}
void Mover::goUp(){
	center[1] = center[1] + moveSpeed;
	eye[1] = eye[1] + moveSpeed;
}
void Mover::goDown(){
	center[1] = center[1] - moveSpeed;
	eye[1] = eye[1] - moveSpeed;
}
void Mover::speedUp(){
	moveSpeed *= 1.2;
}
void Mover::speedDown(){
	moveSpeed /= 1.2;
}
float Mover::getMoveSpeed(){
	return moveSpeed;
}