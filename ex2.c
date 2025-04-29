/**
 * Three Colored Circles on a Grid
 * Drawing demonstration using OpenGL/GLUT
 */

#define GL_SILENCE_DEPRECATION /* Silence deprecation warnings on macOS */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <math.h>

/* Constants */
#define WINDOW_WIDTH     600
#define WINDOW_HEIGHT    600
#define WINDOW_POS_X     50
#define WINDOW_POS_Y     50
#define CIRCLE_SEGMENTS  100
#define GRID_SPACING     0.1f
#define GRID_COLOR       0.7f

/**
 * Draw a filled circle with the specified properties
 */
void drawCircle(float centerX, float centerY, float radius, float red, float green, float blue) {
    glColor3f(red, green, blue);
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY); /* Center point */
    
    for (int i = 0; i <= CIRCLE_SEGMENTS; i++) {
        float angle = 2.0f * M_PI * (float)i / (float)CIRCLE_SEGMENTS;
        float x = centerX + radius * cosf(angle);
        float y = centerY + radius * sinf(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

/**
 * Draw the background grid
 */
void drawGrid(void) {
    glColor3f(GRID_COLOR, GRID_COLOR, GRID_COLOR); /* Light gray */
    
    glBegin(GL_LINES);
    
    /* Vertical lines */
    for (float x = -1.0f; x <= 1.0f; x += GRID_SPACING) {
        glVertex2f(x, -1.0f);
        glVertex2f(x, 1.0f);
    }
    
    /* Horizontal lines */
    for (float y = -1.0f; y <= 1.0f; y += GRID_SPACING) {
        glVertex2f(-1.0f, y);
        glVertex2f(1.0f, y);
    }
    
    glEnd();
}

/**
 * GLUT display callback
 */
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    /* Draw background grid */
    drawGrid();

    /* Draw three colored circles */
    drawCircle(-0.5f, 0.6f, 0.1f, 1.0f, 0.0f, 0.0f); /* Red */
    drawCircle(-0.3f, 0.7f, 0.1f, 0.0f, 1.0f, 0.0f); /* Green */
    drawCircle(-0.4f, 0.5f, 0.1f, 0.0f, 0.0f, 1.0f); /* Blue */

    glFlush();
}

/**
 * Initialize OpenGL settings
 */
void setup(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0); /* White background */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

/**
 * GLUT keyboard callback for basic controls
 */
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: /* Escape key */
            exit(0);
            break;
    }
}

int main(int argc, char** argv) {
    /* Initialize GLUT */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
    glutCreateWindow("Three Colored Circles on a Grid");
    
    /* Set up callbacks */
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    
    /* Initialize OpenGL state */
    setup();
    
    /* Enter main loop */
    glutMainLoop();
    return 0;
}
