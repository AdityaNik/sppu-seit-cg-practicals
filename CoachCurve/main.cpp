#include<iostream>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>
using namespace std;
float oldX,oldY;
int i=3;

void init(){
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(0,0,0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,700,0,700);


}
void koch(GLdouble dir,GLfloat len,GLfloat itr){
    float newX;
    float newY;
    float rdir=3.14/180.0*dir;
    newX=oldX+len*cos(rdir);
    newY=oldY+len*sin(rdir);

    if(itr==0){
        glVertex2f(oldX,oldY);
        glVertex2f(newX,newY);
        oldX=newX;
        oldY=newY;

    }else{
        itr--;
        koch(dir,len,itr);
        dir+=60;
        koch(dir,len,itr);
        dir-=120;
        koch(dir,len,itr);
        dir+=60;
        koch(dir,len,itr);
    }

}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINE_LOOP);
    koch(0,4,i);
    koch(-120,4,i);
    koch(120,4,i);
    glEnd();

    glFlush();
}



void mouse(int btn,int state,int x,int y){
    if(state==GLUT_DOWN){
        if(btn==GLUT_LEFT_BUTTON){
            oldX=x;
            oldY=(700-y);
            display();
        }
        if(btn==GLUT_RIGHT_BUTTON){
            i++;
        }

    }

}

int main(int argv,char** argc){
    glutInit(&argv,argc);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutInitWindowPosition(200,100);
    glutInitWindowSize(700,700);
    glutCreateWindow("Coach Curve");

    glutMouseFunc(mouse);
    glutDisplayFunc(display);
    init();

    glutMainLoop();


}
