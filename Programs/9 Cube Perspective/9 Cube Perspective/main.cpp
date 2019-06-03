//
//  main.cpp
//  9 Cube Perspective
//
//  Created by Mohammed Ataa on 06/05/19.
//  Copyright © 2019 Ataago. All rights reserved.
//
//  Program to draw a color cube and allow the user to move the camera to experiment with perspective viewing .Use OpenGL functions.

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"  // Remove deprecation warnings in MacOS

#include <GLUT/GLUT.h>


GLfloat colors[] = {
    1, 1, 1,
    1, 1, 0,
    1, 0, 1,
    0, 1, 1,
    0, 0, 1,
    0, 1, 0,
    1, 0, 0,
    0, 0, 0
};
GLfloat vertices_n_normals[] = {
    -1, -1, -1,
     1, -1, -1,
     1,  1, -1,
    -1,  1, -1,
    -1, -1,  1,
     1, -1,  1,
     1,  1,  1,
    -1,  1,  1,
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
int theta[3] = {0, 0, 0};
GLdouble viewer[3] = {0, 0, 5};

void myReshape(int w, int h);
void myDisplay();
void myMouse(int button, int state, int x, int y);
void myKeyboard(unsigned char key, int x, int y);
void myIdle();


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Program 9");
    
    glutReshapeFunc(myReshape);
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouse);
    glutKeyboardFunc(myKeyboard);
    glutIdleFunc(myIdle);
    
    glEnable(GL_DEPTH_TEST);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glVertexPointer(3, GL_FLOAT, 0, vertices_n_normals);
    glNormalPointer(GL_FLOAT, 0, vertices_n_normals);
    
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
        glFrustum(-2 * aspect_ratio, 2 * aspect_ratio, -2, 2, 1, 20);
    else
        glFrustum(-2, 2, -2 / aspect_ratio, 2 / aspect_ratio, 1, 20);
    glMatrixMode(GL_MODELVIEW);
}
void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    gluLookAt(viewer[0], viewer[1], viewer[2], 0, 0, 0, 0, 1, 0);
    glRotated(theta[0], 1, 0, 0);
    glRotated(theta[1], 0, 1, 0);
    glRotated(theta[2], 0, 0, 1);
    
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);
    glutSwapBuffers();
}

void myMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        axis = 0;
    if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
        axis = 1;
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        axis = 2;
}
void myKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'x': viewer[0] -= 1; break;
        case 'X': viewer[0] += 1; break;
        case 'y': viewer[1] -= 1; break;
        case 'Y': viewer[1] += 1; break;
        case 'z': viewer[2] -= 1; break;
        case 'Z': viewer[2] += 1; break;
        default: break;
    }
    glutPostRedisplay();
}
void myIdle()
{
    theta[axis] += 1;
    if (theta[axis] > 360)
        theta[axis] -= 360;
    glutPostRedisplay();
}

