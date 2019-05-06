//
//  main.cpp
//  7 Cube GLRotate
//
//  Created by Mohammed Ataa on 05/05/19.
//  Copyright © 2019 Ataago. All rights reserved.
//
//  Program to draw a color cube and spin it using openGL transformation matrices

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"  // Remove deprecation warnings in MacOS

#include <GLUT/GLUT.h>

GLfloat colors[] = {
    1, 0, 0,
    1, 1, 0,
    0, 1, 0,
    0, 1, 1,
    1, 0, 1,
    0, 0, 1,
    1, 1, 1,
    0, 0, 0
};

GLfloat vertices[] = {
    -1, -1, -1,
    1, -1, -1,
    1,  1, -1,
    -1,  1, -1,
    -1, -1,  1,
    1, -1,  1,
    1,  1,  1,
    -1,  1,  1
};

GLfloat normals[] = {
    -1, -1, -1,
    1, -1, -1,
    1,  1, -1,
    -1,  1, -1,
    -1, -1,  1,
    1, -1,  1,
    1,  1,  1,
    -1,  1,  1
};

GLubyte cubeIndices[] = {
    0, 3, 2, 1,
    2, 3, 7, 6,
    4, 5, 6, 7,
    0, 1, 5, 4,
    1, 2, 6, 5,
    0, 4, 7, 3
};

int axis = 0;
int theta[] = {0, 0, 0};

void myReshape(int w, int h);
void myDisplay();
void myMouse(int button, int state, int x, int y);
void myIdle();

void myInit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, -2, 2);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("program 7");
    
    myInit();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouse);
    glutIdleFunc(myIdle);
    
    glEnable(GL_DEPTH_TEST);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT, 0, normals);
    
    glutMainLoop();
    return 0;
}

void myReshape(int w, int h)
{
    double aspect_ratio = w / h;
    
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w > h)
        glOrtho(-2 * aspect_ratio, 2 * aspect_ratio, -2, 2, -2, 2);
    else
        glOrtho(-2, 2, -2 / aspect_ratio, 2 / aspect_ratio, -2, 2);
    glMatrixMode(GL_MODELVIEW);
}
void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    glRotated(theta[0], 1, 0, 0);
    glRotated(theta[1], 0, 1, 0);
    glRotated(theta[2], 0, 0, 1);
    
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);
    glutSwapBuffers();
}

void myMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        axis = 0;   // x axis
    if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
        axis = 1;   // y axis
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        axis = 2;   // z axis
}
void myIdle()
{
    theta[axis] += 2;
    if (theta[axis] > 360)
        theta[axis] -= 360;
    glutPostRedisplay();
}
