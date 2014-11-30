#include "Jumper.h"
#include <cstdio>
#include <cmath>

Jumper::Jumper(float & eye, float & center) :eye(eye), center(center), land(eye), move(false)
{
    acceleration = 2.0*height / (time*time);
    initialSpeed = sqrt(2 * acceleration*height);
}

Jumper::~Jumper()
{
}

void Jumper::jump()
{
    move = true;
    speed = initialSpeed;
}

void Jumper::oneFrame()
{
    if (move) {
        speed -= acceleration;
        if (eye + speed > land) {
            eye += speed;
            center += speed;
            //printf("%d\n");
        }
        else {
            move = false;
        }
    }
}
