//
//  main.cpp
//  2 Sierpinski 3D
//
//  Created by Mohammed Ataa on 05/05/19.
//  Copyright © 2019 Ataago. All rights reserved.
//
//  Program to recursively subdivide a tetrahedron to form 3D Sierpinski gasket. The number of recursive steps is to be specified by the user.

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"  // Remove deprecation warnings in MacOS

#include <GLUT/GLUT.h>
int n = 3;   // Times the Tetrahedron is Recursivily Divided
double vertices[4][3] = {{0, 0, 250}, {-250, -200, 0}, {250, -200, 0}, {0, 250, 0}};    // A, B, C, D
double colors[4][3] = {{1, 0 ,0}, {0, 1, 0}, {0, 0, 1}, {0, 0, 0}}; // R G B black


void myDisplay();
void div_tetrahedron(double A[3], double B[3], double C[3], double D[3], int n);
void draw_tetrahedron(double A[3], double B[3], double C[3], double D[3]);
void draw_triangle(double A[3], double B[3], double C[3]);


void myInit()
{
    glEnable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-500, 500, -500, 500, -500, 500);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);    // Single buffer with RGB colors
    
    glutInitWindowPosition(50, 0);     // Postion of Window on my Screen wrt to top left corner
    glutInitWindowSize(1000, 1000);   // Window Size wrt to pixels
    glutCreateWindow("Program 2");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMainLoop();
    return 0;
}


void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glBegin(GL_TRIANGLES);
    div_tetrahedron(vertices[0], vertices[1], vertices[2], vertices[3], n);
    glEnd();
    
    glFlush();
}

void div_tetrahedron(double A[3], double B[3], double C[3], double D[3], int n)
{
    if (n == 0)      // If no divisions required Draw Tetrahedron
    {
        draw_tetrahedron(A, B, C, D);
    }
    else    // Divide the Tetrahedron into 4 terahedrons with its 6 edges mid points individually
    {
        double AB[3], BC[3], CA[3], AD[3], BD[3], CD[3];
        
        for (int i = 0; i < 3; i++) // Loop for x, y, z coordinates
        {
            AB[i] = (A[i] + B[i]) / 2;  // Mid point on the edge AB
            BC[i] = (B[i] + C[i]) / 2;  // Mid point on the edge BC
            CA[i] = (C[i] + A[i]) / 2;  // Mid point on the edge CA
            AD[i] = (A[i] + D[i]) / 2;  // Mid point on the edge AD
            BD[i] = (B[i] + D[i]) / 2;  // Mid point on the edge BD
            CD[i] = (C[i] + D[i]) / 2;  // Mid point on the edge CD
        }
        
        div_tetrahedron(A, AB, CA, AD, n - 1);  // Top Tetra
        div_tetrahedron(AB, B, BC, BD, n - 1);  // Left Tetra
        div_tetrahedron(CA, BC, C, CD, n - 1);  // Righ Tetra
        div_tetrahedron(AD, BD, CD, D, n - 1);  // Behind Tetra
    }
}

void draw_tetrahedron(double A[3], double B[3], double C[3], double D[3])
{
    glColor3dv(colors[0]); draw_triangle(A, B, C);     // Front Triangle Red
    glColor3dv(colors[1]); draw_triangle(A, C, D);     // Right Triangle Green
    glColor3dv(colors[2]); draw_triangle(A, B, D);     // Left Triangle Blue
    glColor3dv(colors[3]); draw_triangle(B, C, D);     // Bottom Triangle Black
}

void draw_triangle(double A[3], double B[3], double C[3])
{
    glVertex2dv(A);
    glVertex2dv(B);
    glVertex2dv(C);
}
