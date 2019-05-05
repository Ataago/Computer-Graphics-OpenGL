//
//  main.cpp
//  4 Scanline Filling
//
//  Created by Mohammed Ataa on 05/05/19.
//  Copyright © 2019 Ataago. All rights reserved.
//
//  Program to fill any given polygon using scan-line area filling algorithm. (Use appropriate data structures)
//

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"  // Remove deprecation warnings in MacOS

#include <GLUT/GLUT.h>

int left_edge[500], right_edge[500];
int x1 = 100, y1 = 250;
int x2 = 250, y2 = 100;
int x3 = 400, y3 = 250;
int x4 = 250, y4 = 400;


void myDisplay();
void scanline_Filling(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
void edge_Detect(int x1, int y1, int x2, int y2);
void draw_pixel(int x, int y);

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
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Program 4");
    
    myInit();
    
    glutDisplayFunc(myDisplay);
    glutMainLoop();
    return 0;
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    scanline_Filling(x1, y1, x2, y2, x3, y3, x4, y4);
    
    
//    // Test Boundary
//    glBegin(GL_LINE_LOOP);
//    glVertex2i(x1, y1);
//    glVertex2i(x2, y2);
//    glVertex2i(x3, y3);
//    glVertex2i(x4, y4);
//    glEnd();
    
    glFlush();
}

void scanline_Filling(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    for (int i = 0; i < 500; i++)
    {
        left_edge[i] = 500;     // Intial value
        right_edge[i] = 0;
    }
    
    // Test edge for individual lines
    edge_Detect(x1, y1, x2, y2);
    edge_Detect(x2, y2, x3, y3);
    edge_Detect(x3, y3, x4, y4);
    edge_Detect(x4, y4, x1, y1);
    
    for (int y = 0; y < 500; y++)
    {
        if (left_edge[y] <= right_edge[y])
        {
            for (int x = left_edge[y]; x < right_edge[y]; x++)
            {
                draw_pixel(x, y);
            }
        }
    }
    
}

void edge_Detect(int x1, int y1, int x2, int y2)
{
    // Slope shouldnt be in Negative
    if (y2 < y1)    // Swap the lines
    {
        int temp;
        
        temp = x1;
        x1 = x2;
        x2 = temp;
        
        temp = y1;
        y1 = y2;
        y2 = temp;
    }
    
    // Calculate Increment of X if line is parallel or.. find reciprocol of slope
    double increment_x = (y2 == y1)? (x2 - x1) : (x2 - x1) / (y2 - y1);
    
    double x = x1;  // Initial value of x
    for (int y = y1; y < y2; y++)   // while y stays in the line
    {
        left_edge[y] = (x < left_edge[y])? x : left_edge[y];
        right_edge[y] = (x > right_edge[y])? x : right_edge[y];
        x += increment_x;
    }
}

void draw_pixel(int x, int y)   // Plot a point at (x, y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}
