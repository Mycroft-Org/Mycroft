#ifndef _BULLETS_H
#define _BULLETS_H

class Bullets
{
public:
    Bullets(float *eye, float *center);
    ~Bullets();
    void fire();
    void render();

private:
    float * eye;
    float * center;
};


#endif