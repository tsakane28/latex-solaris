#include <GLUT/glut.h>
#include <math.h>

#define M_PI 3.14159265358979323846

const int numSegments = 100;

void drawCircle(float centerX, float centerY, float radius, float red, float green, float blue) {
    glColor3f(red, green, blue);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY);
    for (int i = 0; i <= numSegments; i++) {
        float angle = 2.0f * M_PI * (float)i / (float)numSegments;
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

void drawGrid() {
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_LINES);
    for (float x = -1.0f; x <= 1.0f; x += 0.1f) {
        glVertex2f(x, -1.0f);
        glVertex2f(x, 1.0f);
    }
    for (float y = -1.0f; y <= 1.0f; y += 0.1f) {
        glVertex2f(-1.0f, y);
        glVertex2f(1.0f, y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawGrid();

    drawCircle(-0.5f, 0.6f, 0.1f, 1.0f, 0.0f, 0.0f); // Red
    drawCircle(-0.3f, 0.7f, 0.1f, 0.0f, 1.0f, 0.0f); // Green
    drawCircle(-0.4f, 0.5f, 0.1f, 0.0f, 0.0f, 1.0f); // Blue

    glFlush();
}

void setup() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Three Colored Circles on a Grid");
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(50, 50);
    setup();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
