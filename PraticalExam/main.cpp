#include<stdlib.h>
#include<iostream>
#include<GL/glut.h>
using namespace std;

int h = 0;
int k = 0;

void init(){
    glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0,0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500, 500, -500, 500);
}


void display(){
    glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);
	for(int i = -500; i <= 500; i++){
        glVertex2i(i, 0);
        glVertex2i(0, i);
	}
	glEnd();

	glFlush();
}


void simpleCircle(float r){

    int d = 3 - 2 * r;
    int x = 0;
    int y = r;

    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();

    while(x <= y){
        if(d <= 0){
            d = d + 4 * x + 6;
            x++;
        }else{
            d = d + 4 * (x - y) + 10;
            y--;
            x++;
        }


        glBegin(GL_POINTS);
        glVertex2f(x + h, y + k);
		glVertex2f(-x + h, -y + k);
		glVertex2f(y + h, x + k);
		glVertex2f(-y + h, -x + k);
		glVertex2f(-y + h, x + k);
		glVertex2f(y + h, -x + k);
		glVertex2f(-x + h, y + k);
		glVertex2f(x + h, -y + k);
        glEnd();
    }
    glFlush();
}

void olympicCircle(float r, int a, int b){
    int d = 3 - 2 * r;
    int x = 0;
    int y = r;

    glBegin(GL_POINTS);
    glVertex2i(x, y);

    glEnd();
    while(x <= y){
        if(d <= 0){
            d = d + 4 * x + 6;
            x++;
        }else{
            d = d + 4 * (x - y) + 10;
            y--;
            x++;
        }


        glBegin(GL_POINTS);
        glVertex2f(x + a, y + b);
		glVertex2f(-x + a, -y + b);
		glVertex2f(y + a, x + b);
		glVertex2f(-y + a, -x + b);
		glVertex2f(-y + a, x + b);
		glVertex2f(y + a, -x + b);
		glVertex2f(-x + a, y + b);
		glVertex2f(x + a, -y + b);
        glEnd();
    }
    glFlush();
}

void concentricCircle(int r){
    int d = 3 - 2 * r;
    int x = 0;
    int y = r;

    glBegin(GL_POINTS);
    glVertex2i(x, y);

    glEnd();
    while(x <= y){
        if(d <= 0){
            d = d + 4 * x + 6;
            x++;
        }else{
            d = d + 4 * (x - y) + 10;
            y--;
            x++;
        }


        glBegin(GL_POINTS);
        glVertex2f(x + h, y + k);
		glVertex2f(-x + h, -y + k);
		glVertex2f(y + h, x + k);
		glVertex2f(-y + h, -x + k);
		glVertex2f(-y + h, x + k);
		glVertex2f(y + h, -x + k);
		glVertex2f(-x + h, y + k);
		glVertex2f(x + h, -y + k);
        glEnd();
    }
    glFlush();
}

void spiralCircle(int turns){
    int radius = 50;
    int x;
    int y;
    int d;
    for(int i = 0; i < turns; i++){
        h = h + 50;
        x = 0;
        y = radius;
        d = 3 - 2 * radius;

        while(x <= y){
            if(d <= 0){
                d = d + 4 * x + 6;
            }else{
                d = d + 4 * (x -y) + 10;
                y--;
            }
            x++;
            glBegin(GL_POINTS);
            glVertex2f(x + h, y + k);
            glVertex2f(-x + h, y + k);
            glVertex2f(y + h, x + k);
            glVertex2f(-y + h, x + k);
            glEnd();
        }


        radius = radius + 50;
        h = h - 50;
        x = 0;
        y = radius;
        d = 3 - 2 * radius;

        while(x <= y){
            if(d <= 0){
                d = d + 4 * x + 6;
            }else{
                d = d + 4 * (x -y) + 10;
                y--;
            }
            x++;
            glBegin(GL_POINTS);
            glVertex2f(x + h, -y + k);
            glVertex2f(-x + h, -y + k);
            glVertex2f(y + h, -x + k);
            glVertex2f(-y + h, -x + k);
            glEnd();
        }
        radius = radius + 50;
    }
    glFlush();
}

void menu(int n){
    float r;
    int cnt;
    int turns;
    switch(n){
    case 1:
        cout<<"\n\nEnter Radius for Circle : ";
        cin>>r;
        simpleCircle(r);
        break;

    case 2:
        cout<<"\nEnter Starting Radius: ";
        cin>>r;
        // Upper Rings
		glColor3f(0.0, 0.0, 1.0);
		olympicCircle(r, 3 * r, 6 * r);
		glColor3f(0.0, 0.0, 0.0);
		olympicCircle(r, 5 * r, 6 * r);
		glColor3f(1.0, 0.0, 0.0);
		olympicCircle(r, 7 * r, 6 * r);

		// Lower Rings

		glColor3f(1.0, 1.0, 0.0);
		olympicCircle(r, 4 * r, 4.8 * r);
		glColor3f(0.0, 1.0, 0.0);
		olympicCircle(r, 6 * r, 4.8 * r);
		glColor3f(0.0, 0.0, 0.0);
        break;
    case 3:
        cout<<"\n\nEnter The Number of circles you want : ";
        cin>>cnt;
        cout<<"\nEnter Starting Radius: ";
        cin>>r;
        concentricCircle(r);
        for(int i = 0; i < cnt; i++){
            r += 20;
            concentricCircle(r);
        }

        break;
    case 4:
        cout<<" \n\nEnter Number of turns you want : ";
        cin>>turns;
        spiralCircle(turns);
        break;
    }
}



int main(int argc, char ** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Circles");

    glutDisplayFunc(display);
    glutCreateMenu(menu);
    glutAddMenuEntry("Simple Circle", 1);
    glutAddMenuEntry("Olympic Circle", 2);
    glutAddMenuEntry("Concentric Circle", 3);
    glutAddMenuEntry("Spiral Circle", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    init();
    glutMainLoop();
}
