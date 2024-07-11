#include<iostream>
#include<stdlib.h>
#include<GL/glut.h>
using namespace std;

float x1,x2,y1,y2;
int steps;
int x,y;
int interchange;
int dx,dy,S1,S2;
void init()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(0,0,0);
    glPointSize(5);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500,500,-500,500);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    for(int i=-500; i<500; i++)
    {

        glVertex2i(i,0);
        glVertex2i(0,i);
    }
    glEnd();
    glFlush();


}
int Sign(float x)
{
    if(x>0)
    {
        return 1;
    }
    else if(x==0)
    {
        return 0;
    }
    else
    {
        return -1;
    }

}
void DDA(float x1,float y1,float x2,float y2)
{
    float xinc,yinc;



    dx=(x2-x1);
    dy=(y2-y1);

    if(abs(dx)>=abs(dy))
    {
        steps=abs(dx);

    }
    else
    {
        steps=abs(dy);
    }

    xinc=dx/steps;
    yinc=dy/steps;

    x=x1+0.5*Sign(xinc);
    y=y1+0.5*Sign(yinc);

    glBegin(GL_POINTS);
    int i=1;
    while(i<=steps)
    {

        x=x+xinc;
        y=y+yinc;
        glVertex2i(x,y);
        i++;
    }
    glEnd();
    glFlush();



}

void Bresenham(int x1,int y1,int x2,int y2)
{
    int x=x1;
    y=y1;
    float e;
    dx=abs(x2-x1);
    dy=abs(y2-y1);
    S1=Sign(dx);
    S2=Sign(dy);

    if(dy>dx)
    {
        swap(dx,dy);
        interchange=1;
    }
    else
    {
        interchange=0;
    }
    e=2*dy-dx;

    for(int i=0; i<=dx; i++)
    {
        glBegin(GL_POINTS);
        glVertex2i(x,y);
        while(e>=0)
        {
            if(interchange==1)
            {
                x=x+S1;
            }
            else
            {
                y=y+S2;
            }
            e=e-2*dx;
        }
        if(interchange==1){
            y=y+S2;
        }
        else{
            x=x+S1;
        }
        e=e+2*dy;
        glEnd();
    }
    glFlush();



}
void menu(int n)
{
    switch(n)
    {

    case 1:
        cout<<"Enter the Value of x1"<<endl;
        cin>>x1;
        cout<<"Enter the Value of Y1"<<endl;
        cin>>y1;

        cout<<"Enter the Value of x2"<<endl;
        cin>>x2;
        cout<<"Enter the Value of Y2"<<endl;
        cin>>y2;

        DDA(x1,y1,x2,y2);
        break;

    case 2:
        cout<<"Enter the Value of x1"<<endl;
        cin>>x1;
        cout<<"Enter the Value of Y1"<<endl;
        cin>>y1;

        cout<<"Enter the Value of x2"<<endl;
        cin>>x2;
        cout<<"Enter the Value of Y2"<<endl;
        cin>>y2;

        Bresenham(x1,y1,x2,y2);
        break;

    }

}
int main(int argv,char** argc)
{
    glutInit(&argv,argc);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutInitWindowPosition(200,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("DDA");

    glutDisplayFunc(display);

    glutCreateMenu(menu);
    glutAddMenuEntry("DDA Simple",1);
    glutAddMenuEntry("DDA Dotted",2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    init();
    glutMainLoop();

}
