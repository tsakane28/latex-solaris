#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 0.5f);   

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(-0.5f, -0.5f); 

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(0.5f, -0.5f); 

    glEnd();

    glFlush();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Colored Triangle");
    glutInitWindowSize(500, 500); 
    glutInitWindowPosition(100, 100); 
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
