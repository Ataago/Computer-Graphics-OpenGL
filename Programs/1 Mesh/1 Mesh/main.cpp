//
//  main.cpp
//  1 Mesh
//
//  Created by Mohammed Ataa on 05/05/19.
//  Copyright © 2019 Ataago. All rights reserved.
//
//  Program to display a set of values {fij} as a rectangular mesh.

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"  // Remove deprecation warnings in MacOS

#include <GLUT/GLUT.h>

// M x N rectangluar mesh
#define MAX_X 15
#define MAX_Y 15

// W x H of Rectangle (width x Height)
#define CELL_W 20
#define CELL_H 20

void myDisplay();
void myInit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    // Single buffer with RGB colors
    
    glutInitWindowPosition(50, 50);     // Postion of Window on my Screen wrt to top left corner
    glutInitWindowSize(500, 500);   // Window Size wrt to pixels
    glutCreateWindow("Program 1");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMainLoop();
    return 0;
}


void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    for (int x = CELL_W; x < MAX_X * CELL_W; x += CELL_W)
    {
        for (int y = CELL_H; y < MAX_Y * CELL_H; y += CELL_H)
        {
            glBegin(GL_LINE_LOOP);
            glVertex2d(x, y);
            glVertex2d(x + CELL_W, y);
            glVertex2d(x + CELL_W, y + CELL_H);
            glVertex2d(x, y + CELL_H);
            glEnd();
        }
    }
    
    glFlush();
}
