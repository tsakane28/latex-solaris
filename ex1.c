/**
 * Colored Triangle Demo
 * Simple OpenGL/GLUT demonstration for drawing a shaded triangle
 */

#define GL_SILENCE_DEPRECATION /* Silence deprecation warnings on macOS */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

/* Constants */
#define WINDOW_WIDTH     500
#define WINDOW_HEIGHT    500
#define WINDOW_POS_X     100
#define WINDOW_POS_Y     100

/**
 * GLUT display callback
 */
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    /* Draw the colored triangle */
    glBegin(GL_TRIANGLES);
    
    /* Red vertex (top) */
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 0.5f);
    
    /* Green vertex (bottom left) */
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(-0.5f, -0.5f);
    
    /* Blue vertex (bottom right) */
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(0.5f, -0.5f);
    
    glEnd();

    glFlush();
}

/**
 * Initialize OpenGL settings
 */
void init(void) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  /* White background */
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
    glutCreateWindow("Colored Triangle");
    
    /* Set up callbacks */
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    
    /* Initialize OpenGL state */
    init();
    
    /* Enter main loop */
    glutMainLoop();
    return 0;
}
