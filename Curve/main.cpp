#include<iostream>
#include<stdlib.h>
#include<GL/glut.h>
using namespace std;

GLfloat point[4][2];
int k=0;

void init(){
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(0,0,0);
	glPointSize(5);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,500,0,500);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);

	glFlush();
}

void drawLine(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2){
	glBegin(GL_LINE_LOOP);
	glVertex2f(x1,y1);
	glVertex2f(x2,y2);
	glEnd();
	glFlush();
}

void midPointSubdivision(GLfloat x1,GLfloat y1,GLfloat x2, GLfloat y2, GLfloat x3,GLfloat y3,GLfloat x4,GLfloat y4){
	GLfloat xAB = (x1 + x2) / 2;
	GLfloat yAB = (y1 + y2) / 2;
	GLfloat xBC = (x2 + x3) / 2;
	GLfloat yBC = (y2 + y3) / 2;
	GLfloat xCD = (x3 + x4) / 2;
	GLfloat yCD = (y3 + y4) / 2;

	GLfloat xABC = (xAB + xBC) / 2;
	GLfloat yABC = (yAB + yBC) / 2;
	GLfloat xBCD = (xBC + xCD) / 2;
	GLfloat yBCD = (yBC + yCD) / 2;

	GLfloat xABCD = (xABC + xBCD) / 2;
	GLfloat yABCD = (yABC + yBCD) / 2;

	if((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) > 4 || (x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2) > 4 || (x4 - x3) * (x4 - x3) + (y4 - y3) * (y4 - y3)> 4){
		midPointSubdivision(x1, y1, xAB, yAB, xABC, yABC, xABCD, yABCD);
		midPointSubdivision(xABCD, yABCD, xBCD, yBCD, xCD, yCD, x4, y4);
	}
	else{
		drawLine(x1, y1, xABCD, yABCD);
		drawLine(xABCD, yABCD, x4, y4);
	}
}

void mouse(int btn, int state, int x, int y){
	if(state == GLUT_DOWN){
		if(btn == GLUT_LEFT_BUTTON){
			point[k][0] = (float)(x);
			point[k][1] = (float)(500-y);

			glBegin(GL_POINTS);
			glVertex2f(point[k][0], point[k][1]);
			glEnd();
			glFlush();
			k++;
		}

		if(btn==GLUT_RIGHT_BUTTON){
			drawLine(point[0][0], point[0][1], point[1][0], point[1][1]);
			drawLine(point[1][0], point[1][1], point[2][0], point[2][1]);
			drawLine(point[2][0], point[2][1], point[3][0], point[3][1]);
			midPointSubdivision(point[0][0], point[0][1],
                                point[1][0], point[1][1],
                                point[2][0], point[2][1],
                                point[3][0], point[3][1]);
		}
	}
}

int main(int argv ,char** argc){
	glutInit(&argv,argc);
	glutInitDisplayMode(GLUT_RGB |GLUT_SINGLE);

	glutInitWindowPosition(200,100);
	glutInitWindowSize(500,500);
	glutCreateWindow("Bezier Curve");

	glutDisplayFunc(display);
	glutMouseFunc(mouse);

	init();
	glutMainLoop();
}
