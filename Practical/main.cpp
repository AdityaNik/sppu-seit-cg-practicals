#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// Constants for window dimensions
const int width = 500;
const int height = 500;

// Array to store polygon vertices
int arr[100][2];
int n = 0; // Number of vertices
bool isDrawing = false; // Flag to indicate if drawing polygon

using namespace std;

// Function prototypes
void boundaryFill(int x, int y, float fillR, float fillG, float fillB);
void floodFill(int x, int y, float fillR, float fillG, float fillB, float oldR, float oldG, float oldB);
void myinit();
void Display();
void mymenu(int value);
void mymouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);

// Initialize OpenGL settings
void myinit() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set clear color to white
    glMatrixMode(GL_PROJECTION); // Set matrix mode to projection
    glLoadIdentity(); // Load identity matrix
    gluOrtho2D(0, width, 0, height); // Set orthographic viewing volume
}

// Display callback function
void Display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer
    if (isDrawing) {
        glColor3f(0.0, 0.0, 0.0); // Set drawing color to black
        glBegin(GL_LINE_LOOP); // Begin drawing polygon
        for (int i = 0; i < n; i++) {
            glVertex2f(arr[i][0], arr[i][1]); // Add vertices to polygon
        }
        glEnd(); // End drawing polygon
    }
    glFlush(); // Flush OpenGL buffer
}

// Menu callback function
void mymenu(int value) {
    switch (value) {
        case 1:
            cout << "Boundary Fill selected" << endl;
            boundaryFill(250, 250, 0, 0, 0); // Perform boundary fill at seed point (250, 250) with black color
            break;
        case 2:
            cout << "Flood Fill selected" << endl;
            floodFill(250, 250, 255, 165, 0, 1, 1, 1); // Perform flood fill at seed point (250, 250) with orange color
            break;
        case 3:
            cout << "Exit" << endl;
            exit(0); // Exit program
            break;
    }
}

// Boundary fill algorithm
void boundaryFill(int x, int y, float fillR, float fillG, float fillB) {
    float currentColor[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, currentColor); // Read color of current pixel

    // Check if current pixel is boundary color
    if (currentColor[0] == fillR && currentColor[1] == fillG && currentColor[2] == fillB)
        return;

    // Set fill color
    glColor3f(fillR, fillG, fillB);
    // Fill seed point with fill color
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();

    // Recursively fill neighboring pixels
    boundaryFill(x + 1, y, fillR, fillG, fillB);
    boundaryFill(x - 1, y, fillR, fillG, fillB);
    boundaryFill(x, y + 1, fillR, fillG, fillB);
    boundaryFill(x, y - 1, fillR, fillG, fillB);
}

// Flood fill algorithm
void floodFill(int x, int y, float fillR, float fillG, float fillB, float oldR, float oldG, float oldB) {
    if (x < 0 || x >= width || y < 0 || y >= height)
        return;

    float currentColor[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, currentColor); // Read color of current pixel

    // Check if current pixel is old color
    if (currentColor[0] != oldR || currentColor[1] != oldG || currentColor[2] != oldB)
        return;

    // Set fill color
    glColor3f(fillR, fillG, fillB);
    // Fill current pixel with fill color
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();

    // Recursively fill neighboring pixels
    floodFill(x + 1, y, fillR, fillG, fillB, oldR, oldG, oldB);
    floodFill(x - 1, y, fillR, fillG, fillB, oldR, oldG, oldB);
    floodFill(x, y + 1, fillR, fillG, fillB, oldR, oldG, oldB);
    floodFill(x, y - 1, fillR, fillG, fillB, oldR, oldG, oldB);
}

// Mouse callback function
void mymouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Save vertex coordinates on left-click
        arr[n][0] = x;
        arr[n][1] = height - y;
        n++;
        glutPostRedisplay(); // Request redisplay
    } else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
        isDrawing = true; // Start drawing polygon
        glutPostRedisplay(); // Request redisplay
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        glutCreateMenu(mymenu); // Create menu
        glutAddMenuEntry("BOUNDARY FILL ", 1); // Add menu entry for boundary fill
        glutAddMenuEntry("FLOOD FILL", 2); // Add menu entry for flood fill
        glutAddMenuEntry("EXIT", 3); // Add menu entry for exit
        glutAttachMenu(GLUT_RIGHT_BUTTON); // Attach menu to right mouse button
    }
}

// Keyboard callback function
void keyboard(unsigned char key, int x, int y) {
    if (key == ' ') {
        floodFill(250, 250, 255, 165, 0, 1, 1, 1); // Trigger flood fill with orange color at center
    }
}

// Main function
int main(int argc, char **argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode
    glutInitWindowSize(width, height); // Set window size
    glutInitWindowPosition(200, 200); // Set window position
    glutCreateWindow("MY WINDOW"); // Create window with title "MY WINDOW"
    glutDisplayFunc(Display); // Set display callback function
    glutMouseFunc(mymouse); // Set mouse callback function
    glutKeyboardFunc(keyboard); // Set keyboard callback function
    myinit(); // Initialize OpenGL settings
    glutMainLoop(); // Enter GLUT event processing loop
    return 0;
}
