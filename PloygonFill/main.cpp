#include<iostream>
#include<GL/glut.h>
#include<stdlib.h>
using namespace std;
float xi,yi;
float oldColor[3]={1.0,1.0,1.0};
float newColor[3]={1.0,0.0,0.0};
float bColor[3]={0,0,0};

void init(){
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(0,0,0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,500,0,500);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_LOOP);
	glVertex2i(100,100);
	glVertex2i(100,200);
	glVertex2i(200,200);
	glVertex2i(200,100);
	glEnd();
	glFlush();

}

float* getColor(float x,float y){
	float color[3];
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
	return color;
}

void floodFill(float x, float y, float oldColor[3], float newColor[3]){

	float* color = getColor(x,y);
	if(color[0] == newColor[0] && color[1] == newColor[1] && color[2] == newColor[2]){
		return;
	}
	if(color[0] == oldColor[0] && color[1] == oldColor[1] && color[2] == oldColor[2]){
		glBegin(GL_POINTS);
		glColor3f(newColor[0], newColor[1], newColor[2]);
		glVertex2f(x,y);
		glEnd();
		glFlush();

		floodFill(x+1,y,oldColor,newColor);
		floodFill(x-1,y,oldColor,newColor);
		floodFill(x,y+1,oldColor,newColor);
		floodFill(x,y-1,oldColor,newColor);
		return;

	}
	return;
}

void boundaryFill(float x, float y, float bColor[3], float newColor[3]){
	float * color=getColor(x,y);

	if((color[0] != bColor[0] || color[1] != bColor[1] || color[2] != bColor[2]) && (color[0] != newColor[0] || color[1] != newColor[1] || color[2] != newColor[2])){
		glBegin(GL_POINTS);
		glColor3f(newColor[0], newColor[1], newColor[2]);
		glVertex2f(x,y);
		glEnd();
		glFlush();

		boundaryFill(x+1 ,y, bColor, newColor);
		boundaryFill(x-1, y, bColor, newColor);
		boundaryFill(x, y+1, bColor, newColor);
		boundaryFill(x, y-1, bColor, newColor);
		glFlush();

	}
}
void menu(int n){
	switch(n){
		case 1: floodFill(xi,yi,oldColor,newColor);
		break;
		case 2: boundaryFill(xi,yi,bColor,newColor);
		break;
	}
}

void mouse(int btn,int state,int x,int y){
	if(state == GLUT_DOWN){
		if(btn == GLUT_LEFT_BUTTON){
			xi = (float)x;
			yi = (float)(500-y);
		}
		else if(btn==GLUT_RIGHT_BUTTON){
			glutCreateMenu(menu);
			glutAddMenuEntry("Flood Fill",1);
			glutAddMenuEntry("Boundary Fill",2);
			glutAttachMenu(GLUT_RIGHT_BUTTON);
		}
	}
}

int main(int argv,char** argc){
	glutInit(&argv,argc);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

	glutInitWindowPosition(200,100);
	glutInitWindowSize(500,500);
	glutCreateWindow("Polygon Filling");

	glutDisplayFunc(display);
	glutMouseFunc(mouse);

	init();
	glutMainLoop();

}
