#include <GL/glut.h>
#include <cmath>

int windowWidth = 800;
int windowHeight = 600;

void plotPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void drawLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int twoDy = 2 * dy;
    int twoDyMinusDx = 2 * (dy - dx);
    int p = 2 * dy - dx;
    int x, y;

    if (x1 > x2) {
        x = x2;
        y = y2;
        x2 = x1;
    } else {
        x = x1;
        y = y1;
    }

    plotPixel(x, y);

    while (x < x2) {
        x++;
        if (p < 0) {
            p += twoDy;
        } else {
            y++;
            p += twoDyMinusDx;
        }
        plotPixel(x, y);
    }
}

void drawCircle(int xc, int yc, int radius) {
    int x = 0;
    int y = radius;
    int p = 1 - radius;

    // Initial point
    plotPixel(xc, yc + radius);
    
    // For points on other octants
    while (x < y) {
        x++;

        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }

        // All the perimeter points have already been printed
        if (x <= y) {
            plotPixel(xc + x, yc + y);
            plotPixel(xc - x, yc + y);
            plotPixel(xc + x, yc - y);
            plotPixel(xc - x, yc - y);
            plotPixel(xc + y, yc + x);
            plotPixel(xc - y, yc + x);
            plotPixel(xc + y, yc - x);
            plotPixel(xc - y, yc - x);
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0); // Set color to white

    // Draw a line
    drawLine(100, 100, 400, 400);

    // Draw a circle
    drawCircle(500, 300, 50);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Bresenham Line and Circle Drawing");
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
