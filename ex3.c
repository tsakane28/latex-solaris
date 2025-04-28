#include <GL/glut.h>
#include <stdbool.h> 
#include <math.h>

float ballX = 0.0f;
float ballY = 0.0f;
float ballRadius = 0.05f;
float ballSpeedX = 0.01f;
float ballSpeedY = 0.015f;

int windowWidth = 800;
int windowHeight = 600;

bool isMoving = false;

void drawBall() {
    glColor3f(1.0f, 0.0f, 0.0f); 
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(ballX, ballY); 
    for (int i = 0; i <= 100; i++) {
        float angle = i * 2.0f * 3.14159f / 100;
        glVertex2f(ballX + cos(angle) * ballRadius, ballY + sin(angle) * ballRadius);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawBall();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1); 
    glMatrixMode(GL_MODELVIEW);
}

void timer(int value) {
    if (isMoving) {
        ballX += ballSpeedX;
        ballY += ballSpeedY;

        if (ballX + ballRadius > 1.0f || ballX - ballRadius < -1.0f) {
            ballSpeedX = -ballSpeedX;
        }
        if (ballY + ballRadius > 1.0f || ballY - ballRadius < -1.0f) {
            ballSpeedY = -ballSpeedY;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == ' ') {
        isMoving = true;
    }
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Bouncing Ball");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}
