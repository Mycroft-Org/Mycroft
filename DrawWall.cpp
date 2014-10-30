#include "glut.h"

float wall_row[][3] = {
    { 0, 1, 10 },
    { 1, 1, 2 },
    { 1, 9, 10 },
    { 2, 0, 4 },
    { 2, 5, 6 },
    { 2, 7, 9 },
    { 3, 1, 2 },
    { 3, 6, 8 },
    { 3, 9, 10 },
    { 4, 2, 3 },
    { 4, 5, 7 },
    { 4, 8, 9 },
    { 5, 3, 6 },
    { 5, 7, 9 },
    { 6, 0, 2 },
    { 6, 4, 5 },
    { 7, 1, 3 },
    { 7, 5, 10 },
    { 8, 0, 9 }
};

float wall_col[][3] = {
    { 0, 1, 8 },
    { 1, 3, 5 },
    { 2, 0, 1 },
    { 2, 2, 3 },
    { 2, 4, 6 },
    { 3, 1, 2 },
    { 3, 3, 4 },
    { 3, 5, 8 },
    { 4, 1, 2 },
    { 4, 3, 5 },
    { 4, 6, 7 },
    { 5, 0, 3 },
    { 5, 6, 7 },
    { 6, 4, 6 },
    { 7, 1, 2 },
    { 7, 3, 4 },
    { 7, 5, 6 },
    { 8, 0, 1 },
    { 8, 2, 3 },
    { 8, 4, 5 },
    { 8, 6, 7 },
    { 9, 3, 4 },
    { 9, 5, 6 },
    { 10, 0, 7 }
};

float wall_height = 1.0;
float wall_width = 0.06;

void DrawWall()
{
    float center_x, center_y, center_z;
    float scale_x, scale_y, scale_z;

    // Row Walls
    center_z = wall_height / 2;
    scale_y = wall_width;
    scale_z = wall_height;
    for (int i = 0; i < sizeof(wall_row) / sizeof(wall_row[0]); i++) {
        center_x = (wall_row[i][1] + wall_row[i][2]) / 2;
        center_y = (wall_row[i][0]);
        scale_x = wall_row[i][2] - wall_row[i][1];
        glPushMatrix();
        glTranslatef(center_x, center_y, center_z);
        glScalef(scale_x, scale_y, scale_z);
        glutSolidCube(1.0);
        glPopMatrix();
    }

    // Column Walls
    center_z = wall_height / 2;
    scale_x = wall_width;
    scale_z = wall_height;
    for (int i = 0; i < sizeof(wall_col) / sizeof(wall_col[0]); i++) {
        center_y = (wall_col[i][1] + wall_col[i][2]) / 2;
        center_x = (wall_col[i][0]);
        scale_y = wall_col[i][2] - wall_col[i][1];
        glPushMatrix();
        glTranslatef(center_x, center_y, center_z);
        glScalef(scale_x, scale_y, scale_z);
        glutSolidCube(1.0);
        glPopMatrix();
    }
}