#include "Monster.h"

Monster::Monster()
{
    model = glmReadOBJ("eight.obj");
    MonsterInfo mv[] = {
        { true, 1.5, 0.5, 2.5, 0.5, true },
        { true, 2.5, 2.5, 4.5, 2.5, true },
        { true, 7.5, 3.5, 8.5, 3.5, true },
        { false, 6.5, 4.5, 6.5, 4.5, true },
        { false, 9.5, 1.5, 2.5, 1.5, true }
    };
    for (auto info : mv)
        monsterInfos.push_back(info);


}

Monster::~Monster()
{
}

void Monster::render()
{
    for (auto info : monsterInfos) {
        glPushMatrix();
        if (info.row_col == true) {
            glTranslatef(info.now*amplifier, height, -info.line*amplifier);
        }        
        glScalef(0.05, 0.05, 0.05);
        glmDraw(model, GLM_SMOOTH);
        glPopMatrix();
    }
}

void Monster::oneFrame()
{
    for (auto info = monsterInfos.begin();info!=monsterInfos.end();info++) {
        if (info->direction == true) {
            info->now += speed;
            if (info->now >= info->to) {
                info->direction = false;
                info->now = info->to;
            }
        }
        else {
            info->now -= speed;
            if (info->now <= info->from) {
                info->direction = true;
                info->now = info->from;
            }
        }
    }
    if (directionHeight == true) {
        height += speedHeight;
        if (height >= maxHeight) {
            height = maxHeight;
            directionHeight = false;
        }
    }
    else {
        height -= speedHeight;
        if (height <= minHeight) {
            height = minHeight;
            directionHeight = true;
        }
    }
}

