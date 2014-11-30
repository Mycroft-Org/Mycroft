#ifndef _MONSTER_H
#define _MONSTER_H

#include "glm.h"

class Monster
{
public:
    Monster();
    ~Monster();
    void render();

private:
    GLMmodel * model;
};



#endif
