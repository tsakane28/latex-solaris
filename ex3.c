/**
 * Simple Bouncing Ball Animation using OpenGL/GLUT
 */

#define GL_SILENCE_DEPRECATION /* Silence deprecation warnings on macOS */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

/* Constants */
#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600
#define BALL_RADIUS     0.05f
#define BALL_SPEED_X    0.01f
#define BALL_SPEED_Y    0.015f
#define PI              3.14159f
#define FRAME_DELAY_MS  16     /* ~60fps */
#define CIRCLE_SEGMENTS 100

/* Global state */
typedef struct {
    float x;
    float y;
    float radius;
    float speedX;
    float speedY;
    bool isMoving;
} Ball;

Ball ball = {
    .x = 0.0f,
    .y = 0.0f,
    .radius = BALL_RADIUS,
    .speedX = BALL_SPEED_X,
    .speedY = BALL_SPEED_Y,
    .isMoving = false
};

int windowWidth = WINDOW_WIDTH;
int windowHeight = WINDOW_HEIGHT;

/**
 * Draw the ball as a filled circle
 */
void drawBall(void) {
    glColor3f(1.0f, 0.0f, 0.0f); /* Red */
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(ball.x, ball.y); /* Center */
    
    for (int i = 0; i <= CIRCLE_SEGMENTS; i++) {
        float angle = i * 2.0f * PI / CIRCLE_SEGMENTS;
        float x = ball.x + cosf(angle) * ball.radius;
        float y = ball.y + sinf(angle) * ball.radius;
        glVertex2f(x, y);
    }
    glEnd();
}

/**
 * GLUT display callback
 */
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    drawBall();
    glutSwapBuffers();
}

/**
 * GLUT window reshape callback
 */
void reshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

/**
 * Update ball position and handle boundary collisions
 */
void updateBall(void) {
    if (!ball.isMoving) {
        return;
    }
    
    /* Update position */
    ball.x += ball.speedX;
    ball.y += ball.speedY;
    
    /* Handle collisions with boundaries */
    if (ball.x + ball.radius > 1.0f || ball.x - ball.radius < -1.0f) {
        ball.speedX = -ball.speedX;
    }
    
    if (ball.y + ball.radius > 1.0f || ball.y - ball.radius < -1.0f) {
        ball.speedY = -ball.speedY;
    }
}

/**
 * GLUT timer callback
 */
void timer(int value) {
    updateBall();
    glutPostRedisplay();
    glutTimerFunc(FRAME_DELAY_MS, timer, 0);
}

/**
 * GLUT keyboard callback
 */
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case ' ': /* Space bar */
            ball.isMoving = true;
            break;
        case 27: /* Escape key */
            exit(0);
            break;
    }
}

/**
 * Initialize OpenGL settings
 */
void init(void) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); /* White background */
}

int main(int argc, char** argv) {
    /* Initialize GLUT */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Bouncing Ball");
    
    /* Set up callbacks */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(FRAME_DELAY_MS, timer, 0);
    
    /* Initialize OpenGL state */
    init();
    
    /* Enter main loop */
    glutMainLoop();
    return 0;
}
