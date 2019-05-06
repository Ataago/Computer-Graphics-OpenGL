//
//  main.cpp
//  8 House Rotate
//
//  Created by Mohammed Ataa on 06/05/19.
//  Copyright © 2019 Ataago. All rights reserved.
//
//  Program to create a house like figure and rotate about a given fixed point using openGL functions.

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"  // Remove deprecation warnings in MacOS
#include <GLUT/GLUT.h>
#include <math.h>

double house[3][9] = {
    {100, 200, 200, 100, 150, 140, 160, 160, 140},
    {100, 100, 300, 300, 400, 100, 100, 150, 150},
    {  1,   1,   1,   1,   1,   1,   1,   1,   1}
};
double Rotated_house[3][9];
double rot_mat[3][3];

double h = 100, k = 100, theta = -45;

void myDisplay();
void draw_house(double house[3][9]);
void rotate();


void myInit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 500, 0, 500, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Program 8");
    
    myInit();
    glutDisplayFunc(myDisplay);
    
    glutMainLoop();
    return 0;
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    draw_house(house);
    rotate();
    draw_house(Rotated_house);
    
    glFlush();
}

void draw_house(double point[3][9])
{
    glColor3d(1, 0, 0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= 3; i++)
        glVertex3d(point[0][i], point[1][i], point[2][i]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    for (int i = 2; i <= 4; i++)
        glVertex3d(point[0][i], point[1][i], point[2][i]);
    glEnd();
    
    glColor3d(0, 0, 1);
    glBegin(GL_LINE_LOOP);
    for (int i = 5; i <= 8; i++)
        glVertex3d(point[0][i], point[1][i], point[2][i]);
    glEnd();
}

void rotate()
{
    rot_mat[0][0] = cos(theta);
    rot_mat[0][1] = -sin(theta);
    rot_mat[0][2] = -h * (cos(theta) - 1) + k * sin(theta);
    rot_mat[1][0] = sin(theta);
    rot_mat[1][1] = cos(theta);
    rot_mat[1][2] = -k * (cos(theta) - 1) - h * sin(theta);
    rot_mat[2][0] = 0;
    rot_mat[2][1] = 0;
    rot_mat[2][2] = 1;
    
    for (int i = 0; i < 3; i ++)
        for (int j = 0; j < 9; j++)
        {
            Rotated_house[i][j] = 0;
            for (int k = 0; k < 3; k++)
                Rotated_house[i][j] = Rotated_house[i][j] + rot_mat[i][k] * house[k][j];
        }
}
