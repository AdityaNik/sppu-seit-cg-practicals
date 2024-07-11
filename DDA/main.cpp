#include <GL/glut.h>
#include <math.h>
#include <cstdlib>
using namespace std;

int lineStyle = 0; // 0: Simple Line, 1: Dotted Line, 2: Dashed Line, 3: Solid Line
int startX, startY, endX, endY;

void drawLine(int x1, int y1, int x2, int y2) {
    glBegin(GL_POINTS);
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xIncrement = static_cast<float>(dx) / steps;
    float yIncrement = static_cast<float>(dy) / steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; ++i) {
        switch (lineStyle) {
            case 0: // Simple Line
                glVertex2i(x, y);
                break;
            case 1: // Dotted Line
                if (i % 5 == 0)
                    glVertex2i(x, y);
                break;
            case 2: // Dashed Line
                if (i % 10 < 5)
                    glVertex2i(x, y);
                break;
            case 3: // Solid Line
                glVertex2i(x, y);
                break;
        }

        x += xIncrement;
        y += yIncrement;
    }

    glEnd();
    glFlush();
}

void drawBoat() {
    // Your boat drawing logic goes here
    // You can use a combination of GL_POLYGON and GL_LINES to draw the boat shape
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // Set color to white

    drawLine(startX, startY, endX, endY);

    if (lineStyle == 4) // Draw Boat only when lineStyle is 4 (Boat)
        drawBoat();

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        startX = x - glutGet(GLUT_WINDOW_WIDTH) / 2;
        startY = glutGet(GLUT_WINDOW_HEIGHT) / 2 - y;
        endX = startX;
        endY = startY;
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        endX = x - glutGet(GLUT_WINDOW_WIDTH) / 2;
        endY = glutGet(GLUT_WINDOW_HEIGHT) / 2 - y;
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
            lineStyle = key - '0';
            glutPostRedisplay();
            break;
        case 27: // ESC key
            exit(0);
            break;
    }
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(-glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_WIDTH) / 2,
               -glutGet(GLUT_WINDOW_HEIGHT) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL DDA Line Drawing");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
