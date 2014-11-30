#include "Monster.h"

Monster::Monster()
{
    model = glmReadOBJ("eight.obj");
}

Monster::~Monster()
{
}

void Monster::render()
{
    glmDraw(model, GLM_SMOOTH);
}

