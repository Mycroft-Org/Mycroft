wall_row = (
(0,1,10),
(1,1,2),
(1,9,10),
(2,0,4),
(2,5,6),
(2,7,9),
(3,1,2),
(3,6,8),
(3,9,10),
(4,2,3),
(4,5,7),
(4,8,9),
(5,3,6),
(5,7,9),
(6,0,2),
(6,4,5),
(7,1,3),
(7,5,10),
(8,0,9)
);

wall_col=(
(0,1,8),
(1,3,5),
(2,0,1),
(2,2,3),
(2,4,6),
(3,1,2),
(3,3,4),
(3,5,8),
(4,1,2),
(4,3,5),
(4,6,7),
(5,0,3),
(5,6,7),
(6,4,6),
(7,1,2),
(7,3,4),
(7,5,6),
(8,0,1),
(8,2,3),
(8,4,5),
(8,6,7),
(9,3,4),
(9,5,6),
(10,0,7)
)

wall_height = 1.0;
wall_width = 0.2;


file_wall = open("DrawWall.cpp","w")


def printScript():
    file_wall.writelines("    glPushMatrix();\n")
    file_wall.writelines("    glTranslatef(%f, %f, %f);\n"%(center_x, center_y, center_z))
    file_wall.writelines("    glScalef(%f, %f, %f);\n"%(scale_x, scale_y, scale_z))
    file_wall.writelines("    glutSolidCube(1.0);\n")
    file_wall.writelines("    glPopMatrix();\n\n")


file_wall.write('#include "glut.h"\n')
file_wall.write("void DrawWall() {\n")

file_wall.write("    // Row Walls\n")
for wall in wall_row:
    center_x = float(wall[1] + wall[2])/2
    center_y = float(wall[0])
    center_z = wall_height/2
    scale_x = wall[2] - wall[1]
    scale_y = wall_width
    scale_z = wall_height
    printScript()


file_wall.write("    // Column Walls\n")
for wall in wall_col:
    center_y = float(wall[1] + wall[2])/2
    center_x = float(wall[0])
    center_z = wall_height/2
    scale_y = wall[2] - wall[1]
    scale_x = wall_width
    scale_z = wall_height
    printScript()


file_wall.write("}\n") 
file_wall.close()