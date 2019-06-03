//
//  main.cpp
//  10 Teapot
//
//  Created by Mohammed Ataa on 06/05/19.
//  Copyright © 2019 Ataago. All rights reserved.
//
//  Program using openGL functions to draw a simple shaded scene consisting of a teapot on a table. Define suitably the positions and properties of the light source along with the properties of the surfaces of the solid object used in the scene.


#pragma GCC diagnostic ignored "-Wdeprecated-declarations"  // Remove deprecation warnings in MacOS

#include <GLUT/GLUT.h>

void myDisplay();

void myInit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, -1, 100);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Program 10");
    
    myInit();
    glutDisplayFunc(myDisplay);

    glEnable(GL_DEPTH_TEST);
    
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);     // Normal vectors are normalized to unit length after transformation and before lighting.
    glEnable(GL_COLOR_MATERIAL);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glutMainLoop();
    return 0;
}
void wall()
{
    glPushMatrix();
    glScaled(0.1, 1, 1);
    glutSolidCube(1.5);
    glPopMatrix();
}
void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    
    GLfloat mat_ambient[] = {0.7, 0.7, 0.7, 1};
    GLfloat mat_diffuse[] = {0.5, 0.5, 0.5, 1};
    GLfloat mat_specular[] = {1, 1, 1, 1};
    GLfloat mat_shinniness[] = {50};
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shinniness);
    
    GLfloat light_int[] = {1, 1, 1, 1};
    GLfloat light_pos[] = {-10, 20, 10, 1};
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_int);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLoadIdentity();
    gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);
    glColor3d(0.3, 0.3, 0.3);
    
//    glPushMatrix();
//    glTranslated(-1, 0, 0);
//    wall();
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslated(0, 0, 0);
//    glRotated(90, 0, 1, 0);
//    wall();
//    glPopMatrix();
    
    // Table top
    glPushMatrix();
    glScaled(1, 0.1, 1);
    glutSolidCube(1.5);
    glPopMatrix();
    
    
    glColor3d(1, 0, 0);
    // leg
    glPushMatrix();
    glTranslated(-0.65, -0.45, 0.65);
    glScaled(0.1, 0.7, 0.1);
    glutSolidCube(1.5);
    glPopMatrix();
    
    // leg
    glPushMatrix();
    glTranslated(0.65, -0.45, 0.65);
    glScaled(0.1, 0.7, 0.1);
    glutSolidCube(1.5);
    glPopMatrix();
    
    // leg
    glPushMatrix();
    glTranslated(0.65, -0.45, -0.65);
    glScaled(0.1, 0.7, 0.1);
    glutSolidCube(1.5);
    glPopMatrix();
    
    glColor3d(1, 1, 0);
    glPushMatrix();
    glTranslated(0, 0.2, 0);
    glScaled(0.2, 0.2, 0.2);
    glutSolidTeapot(1);
    glPopMatrix();
    glFlush();
}

