#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<GL/glut.h>
using namespace std;

float finalMatrix[100][100];
float userMatrix[100][100];
float tx, ty;
float sx, sy;
float xm, ym;
int k = 0;


void init(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0, 0, 0);
    glPointSize(4);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-250, 250, -250, 250);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);
    for(int i = -500; i < 500; i++){
        glVertex2f(i, 0);
        glVertex2f(0, i);
    }
    glEnd();
    glFlush();
}

void multiply(float arr[3][3]){
    for(int i = 0; i < k; i++){
        finalMatrix[i][0] = (float)(arr[0][0]*userMatrix[i][0] + arr[0][1]*userMatrix[i][1] + arr[0][2]*userMatrix[i][2]);
        finalMatrix[i][1] = (float)(arr[1][0]*userMatrix[i][0] + arr[1][1]*userMatrix[i][1] + arr[1][2]*userMatrix[i][2]);
        finalMatrix[i][2] = (float)(arr[2][0]*userMatrix[i][0] + arr[2][1]*userMatrix[i][1] + arr[2][2]*userMatrix[i][2]);
    }
}


void translation(float tx, float ty){
    float arr[3][3] = {1, 0, tx, 0, 1, ty, 0, 0, 1};
    multiply(arr);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < k; i++){
        glVertex2f(finalMatrix[i][0], finalMatrix[i][1]);
    }
    glEnd();
    glFlush();
}

void scalling(float sx, float sy){
    float arr[3][3] = {sx, 0, 0, 0, sy, 0, 0, 0, 1};
    multiply(arr);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < k; i++){
        glVertex2f(finalMatrix[i][0], finalMatrix[i][1]);
    }
    glEnd();
    glFlush();
}

void rotation(float angle){
    float arr[3][3] = {cos(angle), -(sin(angle)), 0, sin(angle), cos(angle), 0, 0, 0, 1};
    multiply(arr);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < k; i++){
        glVertex2f(finalMatrix[i][0], finalMatrix[i][1]);
    }
    glEnd();
    glFlush();
}

void reflection_x_axis(){
    float arr[3][3] = {1, 0, 0, 0, -1, 0, 0, 0, 1};
    multiply(arr);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < k; i++){
        glVertex2f(finalMatrix[i][0], finalMatrix[i][1]);
    }
    glEnd();
    glFlush();
}

void reflection_y_axis(){
    float arr[3][3] = {-1, 0, 0, 0, 1, 0, 0, 0, 1};
    multiply(arr);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < k; i++){
        glVertex2f(finalMatrix[i][0], finalMatrix[i][1]);
    }
    glEnd();
    glFlush();
}


void reflection_x_equal_y_axis(){
    float arr[3][3] = {0, 1, 0, 1, 0, 0, 0, 0, 1};
    multiply(arr);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < k; i++){
        glVertex2f(finalMatrix[i][0], finalMatrix[i][1]);
    }
    glEnd();
    glFlush();
}

void reflection_about_origin(){
    float arr[3][3] = {-1, 0, 0, 0, -1, 0, 0, 0, 1};
    multiply(arr);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < k; i++){
        glVertex2f(finalMatrix[i][0], finalMatrix[i][1]);
    }
    glEnd();
    glFlush();
}

void reflection_x_eyqal_minus_y_axis(){
    float arr[3][3] = {-1, 0, 0, 0, -1, 0, 0, 0, 1};
    multiply(arr);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < k; i++){
        glVertex2f(finalMatrix[i][0], finalMatrix[i][1]);
    }
    glEnd();
    glFlush();
}

void shearing_x_axis(){
    float shx;
    cout<<"Enter value for shx: ";
    cin>>shx;
    float arr[3][3] = {1, shx, 0, 0, 1, 0, 0, 0, 1};
    multiply(arr);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < k; i++){
        glVertex2f(finalMatrix[i][0], finalMatrix[i][1]);
    }
    glEnd();
    glFlush();
}

void shearing_y_axis(){
    float shy;
    cout<<"Enter value for shy: ";
    cin>>shy;
    float arr[3][3] = {1, 0, 0, shy, 1, 0, 0, 0, 1};
    multiply(arr);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < k; i++){
        glVertex2f(finalMatrix[i][0], finalMatrix[i][1]);
    }
    glEnd();
    glFlush();
}

void rotation_orbi(){
    float angle;
    cout<<"Enter the rotation angle: ";
    cin>>angle;
    angle = angle * (3.14 / 180);
    cout<<"Enter value for Xm: ";
    cin>>xm;
    cout<<"Enter value for Ym: ";
    cin>>ym;


    float arr[3][3] = {cos(angle), sin(angle), 0, -(sin(angle)), cos(angle), 0, (-xm * cos(angle)+ym * sin(angle)+xm), (-xm * sin(angle)-ym * cos(angle)+ym), 1};
    multiply(arr);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < k; i++){
        glVertex2f(finalMatrix[i][0], finalMatrix[i][1]);
    }
    glEnd();
    glFlush();
}

void scalling_orbi(){
    cout<<"Enter value for Xm: ";
    cin>>xm;
    cout<<"Enter value for Ym: ";
    cin>>ym;
    cout<<"Enter value for sx: ";
    cin>>sx;
    cout<<"Enter value for sy: ";
    cin>>sy;

    float arr[3][3] = {sx, 0, 0, 0, sy, 0, (xm * (1 - sx)), (ym * (1 - sy)), 1};
    multiply(arr);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < k; i++){
        glVertex2f(finalMatrix[i][0], finalMatrix[i][1]);
    }
    glEnd();
    glFlush();
}

void translation_menu(int n){
    switch(n){
        case 1: cout<<"Enter value for TX: ";
                cin>>tx;
                translation(tx, ty);
                break;
        case 2: cout<<"Enter value for TY: ";
                cin>>ty;
                translation(tx, ty);
                break;
        case 3: cout<<"Enter value for TX: ";
                cin>>tx;
                cout<<"Enter value for TY: ";
                cin>>ty;
                translation(tx, ty);
                break;
    }
}

void scalling_menu(int n){
    switch(n){
        case 1: cout<<"Enter value for SX: ";
                cin>>sx;
                cout<<"Enter value for SY: ";
                cin>>sy;
                scalling(sx, sy);
                break;
    }
}


void rotation_menu(int n){
    float angle;
    cout<<"Enter angle for rotation: ";
    cin>>angle;
    angle = (angle / (3.14 * 180));

    switch(n){
        case 1: rotation(-(angle));
                break;
        case 2: rotation(angle);
                break;
    }
}

void reflection_menu(int n){
    switch(n){
        case 1: reflection_x_axis();
                break;
        case 2: reflection_y_axis();
                break;
        case 3: reflection_x_equal_y_axis();
                break;
        case 4: reflection_about_origin();
                break;
        case 5: reflection_x_eyqal_minus_y_axis();
                break;
    }
}

void shearing_menu(int n){
    switch(n){
        case 1: shearing_x_axis();
                break;
        case 2: shearing_y_axis();
                break;
    }
}

void rotation_orbi_menu(int n){
    switch(n){
        case 1: rotation_orbi();
                break;
    }
}

void scalling_orbi_menu(int n){
    switch(n){
        case 1: scalling_orbi();
                break;
    }
}

void mouse(int btn, int state, int x, int y){
    if(state == GLUT_DOWN){
        if(btn == GLUT_LEFT_BUTTON){
            userMatrix[k][0] = (float)(x - 250);
            userMatrix[k][1] = (float)(250 - y);
            userMatrix[k][2] = (float)(1);
            glBegin(GL_POINTS);
            glVertex2f(userMatrix[k][0], userMatrix[k][1]);
            glEnd();
            glFlush();
            k++;
        }

        if(btn == GLUT_RIGHT_BUTTON){
            glBegin(GL_LINE_LOOP);
            for(int i = 0; i < k; i++){
                glVertex2f(userMatrix[i][0], userMatrix[i][1]);
            }
            glEnd();
            glFlush();
        }
    }
}

void menu(int n){
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Transformation");

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    int translation_id = glutCreateMenu(translation_menu);
    glutAddMenuEntry("Along X-axis", 1);
    glutAddMenuEntry("Along Y-axis", 2);
    glutAddMenuEntry("Along XY-axis", 3);

    int scalling_id = glutCreateMenu(scalling_menu);
    glutAddMenuEntry("Along XY-axis", 1);

    int rotation_id = glutCreateMenu(rotation_menu);
    glutAddMenuEntry("ClockWise", 1);
    glutAddMenuEntry("Anti-Clockwise", 2);

    int reflection_id = glutCreateMenu(reflection_menu);
    glutAddMenuEntry("About X-axis", 1);
    glutAddMenuEntry("About Y-axis", 2);
    glutAddMenuEntry("About XY-axis", 3);
    glutAddMenuEntry("About Origin", 4);
    glutAddMenuEntry("About X = -Y axis", 5);

    int shearing_id = glutCreateMenu(shearing_menu);
    glutAddMenuEntry("Along X-axis", 1);
    glutAddMenuEntry("Along Y-axis", 2);

    int orbi_id = glutCreateMenu(rotation_orbi_menu);
    glutAddMenuEntry("Rotation about orbitory point", 1);

    int rotation_orbi_id = glutCreateMenu(rotation_orbi_menu);
    glutAddMenuEntry("Rotation about orbitory point", 1);

    int scalling_orbi_id = glutCreateMenu(scalling_orbi_menu);
    glutAddMenuEntry("Scalling about orbitory point", 1);

    glutCreateMenu(menu);
    glutAddSubMenu("Rotation", 1);
    glutAddSubMenu("Scalling", 2);
    glutAddSubMenu("Rotation", 3);
    glutAddSubMenu("Reflection", 4);
    glutAddSubMenu("Shering", shearing_id);
    glutAddSubMenu("Rotation about orbitary point", rotation_orbi_id);
    glutAddSubMenu("Scalling about orbitary point", scalling_orbi_id);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);


    init();
    glutMainLoop();
}
