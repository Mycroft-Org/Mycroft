#ifndef _BULLETS_H
#define _BULLETS_H

#include <vector>
#include <GL\glut.h>

class Bullet
{
public:
    Bullet(float * eye, float * center);
    void update();
    void render();

private:
    float position[3];
    float direction[3];
    int life;
    const float speed = 0.1;
    bool alive;
    

};

class Bullets
{
public:
    Bullets(float *eye, float *center);
    ~Bullets();
    void fire();
    void render();
    void oneFrame();

private:
    float * eye;
    float * center;
    std::vector<Bullet> ware;
    float startpos[3];
    float direction[3];
    bool active;
    long counter;
    const float speed = 0.1;
    const int bulletGap = 1;
    int bulletWaiting;
};


#endif