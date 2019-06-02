//
//  main.cpp
//  3 Cylinder & Cube
//
//  Created by Mohammed Ataa on 05/05/19.
//  Copyright © 2019 Ataago. All rights reserved.
//
//  Program to create a cylinder and a parallelepiped by extruding a circle and a quadrilateral respectively. Allow the user to specify the circle and the quadrilateral.


#pragma GCC diagnostic ignored "-Wdeprecated-declarations"  // Remove deprecation warnings in MacOS

#include <GLUT/GLUT.h>


void myDisplay();

// To draw a cylinder
void draw_cylinder(int height);
void draw_circle(int h, int k, double radius);
void draw_8Pixels(double x, double y, double h, double k);
void draw_Pixel(double x, double y);

// To draw a Parallelepiped
void draw_cuboid(int height);
void draw_parallelogram(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);


void myInit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-500, 500, -500, 500, -500, 500);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    // Single buffer with RGB colors
    
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
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPointSize(1);     // For drawing a circle
    
    draw_cylinder(1);      // Draw a cyliner
    draw_cuboid(15);        // Draw Parallelopiped
    
    glFlush();
}

void draw_cylinder(int height)
{
    for (int y = 0; y < height; y++)
    {
        glBegin(GL_POINTS);
        draw_circle(250, -200 + y * 10, 100);
        glEnd();
    }
}

void draw_circle(int h, int k, double radius)
{
    double d = 1 - radius;
    double x = 0;
    double y = radius;
    
    while (y > x)
    {
        draw_8Pixels(x, y, h, k);
        
        if (d < 0)  // Move East
        {
            d += (2 * x) + 5;
            x++;
        }
        else    // Move South East
        {
            d += 2 * (x - y) + 5;
            x++;
            y--;
        }
    }
}

void draw_8Pixels(double x, double y, double h, double k)
{
    draw_Pixel(x + h, y + k);
    draw_Pixel(-x + h, y + k);
    draw_Pixel(-x + h, -y + k);
    draw_Pixel(x + h, -y + k);
    draw_Pixel(y + h, x + k);
    draw_Pixel(-y + h, x + k);
    draw_Pixel(-y + h, -x + k);
    draw_Pixel(y + h, -x + k);
}

void draw_Pixel(double x, double y)
{
    glVertex2d(x, y);
}


void draw_cuboid(int height)
{
    int x1 = -250, y1 = -250, x2 = -100, y2 = -250, x3 = -100, y3 = -100, x4 = -250, y4 = -100;
    
    
    for (int y = 0; y < height * 5; y += 5)
    {
        //y *= 5;    // increasing the distance betwwen succesive parallelograms
        draw_parallelogram(x1 + y, y1 + y, x2 + y, y2 + y, x3 + y, y3 + y, x4 + y, y4 + y);
        //y /= 5;    // Restoring the value of y
    }
}

void draw_parallelogram(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    glBegin(GL_LINE_LOOP);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glVertex2d(x3, y3);
    glVertex2d(x4, y4);
    glEnd();
}
