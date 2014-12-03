#include "Monster.h"

Monster::Monster(float* eye, float* center) :eye(eye), center(center)
{
    model = glmReadOBJ("eight.obj");
    MonsterInfo mv[] = {
		{ true, 1.5, 0.5, 2.5, 0.5, 1.0, true, true ,false,0},
		{ true, 2.5, 2.5, 4.5, 2.5, 1.0, true, true, false, 0 },
		{ true, 7.5, 3.5, 8.5, 3.5, 1.0, true, true, false, 0 },
		{ false, 6.5, 4.5, 6.5, 4.5, 1.0, true, true, false, 0 },
		{ false, 9.5, 1.5, 2.5, 1.5, 1.0, true, true, false, 0 }
    };
    for (auto info : mv)
        monsterInfos.push_back(info);

}

Monster::~Monster()
{
}
void Monster::render()
{
	float bloodColor[] = { 1.0, 1.0, 0.0, 1.0 };
	float bloodColor_a[] = { 1.0, 0.0, 0.0, 1.0 };
	float defaultColor[] = { 1.0, 1.0, 1.0, 1.0 };
	int i = 0;
	for (auto info : monsterInfos) {
		if (info.alive){
			glPushMatrix();
			if (info.row_col == true) {
				glTranslatef(info.now*amplifier, height, -info.line*amplifier);
			}
			else {
				glTranslatef(info.line*amplifier, height, -info.now*amplifier);
			}
			glPushMatrix();
			glTranslatef(0, 3, 0);
			glScalef(0.1, 0.1, info.hp * 2);
			info.isattack ? monsterInfos[i].count = 100 : monsterInfos[i].count = monsterInfos[i].count;
			if (info.count > 0){
				glMaterialfv(GL_FRONT, GL_AMBIENT, bloodColor_a);
			}
			else 
				glMaterialfv(GL_FRONT, GL_AMBIENT, bloodColor);
			glutSolidCube(1);
			glMaterialfv(GL_FRONT, GL_AMBIENT, defaultColor);
			glPopMatrix();
			glScalef(0.05, 0.05, 0.05);
			glmDraw(model, GLM_SMOOTH);
			glPopMatrix();
		}
		i++;
	}
}

void Monster::oneFrame()
{
	int i = 0;
    for (auto info = monsterInfos.begin();info!=monsterInfos.end();info++) {
		info->now;
		//printf("%d",info->count);
		if (info->count > 0)
		{
			monsterInfos[i].count--;
		}
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
        i++;
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
float calc_dis(float x1, float y1, float x2, float y2){
	float distance;
	distance = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
	return distance;
}
void Monster::conflict(float speed){
	float en_pos[5][3];
	float distance;
	int i = 0;
	for (auto info : monsterInfos){
		if (info.alive){
			if (info.row_col){
				en_pos[i][0] = info.now * 10;
				en_pos[i][1] = 3;
				en_pos[i][2] = -info.line * 10;
			}
			else{
				en_pos[i][0] = info.line * 10;
				en_pos[i][1] = 3;
				en_pos[i][2] = -info.now * 10;
			}
			distance = calc_dis(en_pos[i][0], en_pos[i][2], eye[0], eye[2]);
			if (distance < 3 && eye[1] <= 10){
				if (info.row_col&&!info.direction)
				{
					eye[0] = eye[0] - 0.25 - speed;
					center[0] = center[0] - 0.25 - speed;
				}
				if (info.row_col&&info.direction)
				{
					eye[0] = eye[0] + 0.25 + speed;
					center[0] = center[0] + 0.25 + speed;
				}
				if (!info.row_col&&!info.direction)
				{
					eye[2] = eye[2] + 0.25 + speed;
					center[2] = center[2] + 0.25 + speed;
				}
				if (!info.row_col&&info.direction)
				{
					eye[2] = eye[2] - 0.25 - speed;
					center[2] = center[2] - 0.25 - speed;
				}

			}
			i++;
		}
	}
}

