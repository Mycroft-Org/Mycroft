#ifndef _MONSTER_H
#define _MONSTER_H

#include "glm.h"
#include <vector>

struct MonsterInfo
{
    bool row_col;
    float line;
    float from;
    float to;
    float now;
    bool direction;
};

class Monster
{
public:
	std::vector<MonsterInfo> monsterInfos;
    Monster();
    ~Monster();
    void render();
    void oneFrame();

private:
    GLMmodel * model;
    float position[2];
    
    const float amplifier = 10;
    const float speed = 0.02;

    float height = 3;
    float maxHeight = 3.5;
    float minHeight = 2.5;
    float speedHeight = 0.1;
    bool directionHeight = true;
};



#endif
