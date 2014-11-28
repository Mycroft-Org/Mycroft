#ifndef _JUMPER_H
#define _JUMPER_H

class Jumper
{
public:
    Jumper(float & eye, float & center);
    ~Jumper();
    void jump();
    void oneFrame();

private:

    const float height = 5;
    const float time = 30;  // From end to top
    float acceleration;
    float initialSpeed;

    float speed;
    float & eye;
    float & center;
    float land;
    bool move;
};


#endif