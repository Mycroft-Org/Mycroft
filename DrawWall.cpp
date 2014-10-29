#include "glut.h"
void DrawWall() {
    // Row Walls
    glPushMatrix();
    glTranslatef(5.500000, 0.000000, 0.500000);
    glScalef(9.000000, 0.200000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.500000, 1.000000, 0.500000);
    glScalef(1.000000, 0.200000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(9.500000, 1.000000, 0.500000);
    glScalef(1.000000, 0.200000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.000000, 2.000000, 0.500000);
    glScalef(4.000000, 0.200000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.500000, 2.000000, 0.500000);
    glScalef(1.000000, 0.200000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.000000, 2.000000, 0.500000);
    glScalef(2.000000, 0.200000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.500000, 3.000000, 0.500000);
    glScalef(1.000000, 0.200000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7.000000, 3.000000, 0.500000);
    glScalef(2.000000, 0.200000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(9.500000, 3.000000, 0.500000);
    glScalef(1.000000, 0.200000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.500000, 4.000000, 0.500000);
    glScalef(1.000000, 0.200000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.000000, 4.000000, 0.500000);
    glScalef(2.000000, 0.200000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.500000, 4.000000, 0.500000);
    glScalef(1.000000, 0.200000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.500000, 5.000000, 0.500000);
    glScalef(3.000000, 0.200000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.000000, 5.000000, 0.500000);
    glScalef(2.000000, 0.200000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.000000, 6.000000, 0.500000);
    glScalef(2.000000, 0.200000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.500000, 6.000000, 0.500000);
    glScalef(1.000000, 0.200000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.000000, 7.000000, 0.500000);
    glScalef(2.000000, 0.200000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7.500000, 7.000000, 0.500000);
    glScalef(5.000000, 0.200000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.500000, 8.000000, 0.500000);
    glScalef(9.000000, 0.200000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    // Column Walls
    glPushMatrix();
    glTranslatef(0.000000, 4.500000, 0.500000);
    glScalef(0.200000, 7.000000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.000000, 4.000000, 0.500000);
    glScalef(0.200000, 2.000000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.000000, 0.500000, 0.500000);
    glScalef(0.200000, 1.000000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.000000, 2.500000, 0.500000);
    glScalef(0.200000, 1.000000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.000000, 5.000000, 0.500000);
    glScalef(0.200000, 2.000000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.000000, 1.500000, 0.500000);
    glScalef(0.200000, 1.000000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.000000, 3.500000, 0.500000);
    glScalef(0.200000, 1.000000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.000000, 6.500000, 0.500000);
    glScalef(0.200000, 3.000000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.000000, 1.500000, 0.500000);
    glScalef(0.200000, 1.000000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.000000, 4.000000, 0.500000);
    glScalef(0.200000, 2.000000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.000000, 6.500000, 0.500000);
    glScalef(0.200000, 1.000000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.000000, 1.500000, 0.500000);
    glScalef(0.200000, 3.000000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.000000, 6.500000, 0.500000);
    glScalef(0.200000, 1.000000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.000000, 5.000000, 0.500000);
    glScalef(0.200000, 2.000000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7.000000, 1.500000, 0.500000);
    glScalef(0.200000, 1.000000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7.000000, 3.500000, 0.500000);
    glScalef(0.200000, 1.000000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7.000000, 5.500000, 0.500000);
    glScalef(0.200000, 1.000000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.000000, 0.500000, 0.500000);
    glScalef(0.200000, 1.000000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.000000, 2.500000, 0.500000);
    glScalef(0.200000, 1.000000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.000000, 4.500000, 0.500000);
    glScalef(0.200000, 1.000000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.000000, 6.500000, 0.500000);
    glScalef(0.200000, 1.000000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(9.000000, 3.500000, 0.500000);
    glScalef(0.200000, 1.000000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(9.000000, 5.500000, 0.500000);
    glScalef(0.200000, 1.000000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10.000000, 3.500000, 0.500000);
    glScalef(0.200000, 7.000000, 1.000000);
    glutSolidCube(1.0);
    glPopMatrix();

}
