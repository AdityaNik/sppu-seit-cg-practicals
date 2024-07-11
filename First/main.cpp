#include <GL/glut.h>
#include <cmath>
#include<iostream>
using namespace std;

int windowWidth = 800;
int windowHeight = 600;

void plotPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void upper(int xc, int yc, int x, int y)
{
    plotPixel(xc + x, yc + y);
    plotPixel(xc - x, yc + y);
    plotPixel(xc + y, yc + x);
    plotPixel(xc - y, yc + x);
}

void dipper(int xc, int yc, int x, int y)
{
    plotPixel(xc + x, yc - y);
    plotPixel(xc - x, yc - y);
    plotPixel(xc + y, yc - x);
    plotPixel(xc - y, yc - x);
}

void drawCircle(int xc, int yc, int radius, int n)
{
    int originalRadius = radius;
    int originalXC = xc;
    int cnt = 0;
    for(int i = 1; i <= n; i++)
    {
        int x = 0;
        int y = radius;
        int p = 3 - 2 * radius;

        plotPixel(xc, yc + radius);

        while (x < y)
        {

            x++;
            if (p < 0)
            {
                p += 4 * x + 6;
            }
            else
            {
                y--;
                p += 4 * (x - y) + 10;
            }

            if (x <= y)
            {
                if (cnt == 0)
                {
                    upper(xc, yc, x, y);
                }
                else
                {
                    dipper(xc, yc, x, y);
                }
            }
        }
        if(cnt == 1){
            cnt = 0;
            xc = originalXC;
        }else{
            cnt = 1;
            xc = originalXC + originalRadius;
        }
        yc = 0;
        radius = radius + originalRadius;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);

    int x, y, r, c;
    cout<<"Enter value for X"<<endl;
    cout << "X = ";
    cin>>x;
    cout<<endl;
    cout<<"Enter value for Y"<<endl;
    cout << "Y = ";
    cin>>y;
    cout<<endl;
    cout<<"Enter value for Radius"<<endl;
    cout << "Radius = ";
    cin>>r;
    cout<<endl;
    cout<<"Enter Circles you want"<<endl;
    cout << "Circles = ";
    cin>>c;
    cout<<endl;

    drawCircle(x, y, r, c);

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Bresenham Line and Circle Drawing");
    gluOrtho2D(-windowWidth, windowWidth, -windowHeight, windowHeight);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
