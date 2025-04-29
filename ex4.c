/**
 * Simple 3D Cube
 * Demonstrates drawing a 3D cube using vertex specification
 */

#define GL_SILENCE_DEPRECATION /* Silence deprecation warnings on macOS */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

/* Constants */
#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600
#define WINDOW_POS_X    100
#define WINDOW_POS_Y    100
#define CUBE_SIZE       0.5f  /* Half-length of cube sides */

/* Cube vertex colors (RGBA) */
const GLfloat colors[8][4] = {
    {1.0f, 0.0f, 0.0f, 1.0f}, /* Red */
    {0.0f, 1.0f, 0.0f, 1.0f}, /* Green */
    {0.0f, 0.0f, 1.0f, 1.0f}, /* Blue */
    {1.0f, 1.0f, 0.0f, 1.0f}, /* Yellow */
    {1.0f, 0.0f, 1.0f, 1.0f}, /* Magenta */
    {0.0f, 1.0f, 1.0f, 1.0f}, /* Cyan */
    {1.0f, 0.5f, 0.0f, 1.0f}, /* Orange */
    {0.5f, 0.5f, 0.5f, 1.0f}  /* Gray */
};

/**
 * Draw a cube using individual vertices and colors
 */
void drawCube(void) {
    GLfloat vertices[8][3] = {
        /* Front face vertices */
        {-CUBE_SIZE, -CUBE_SIZE,  CUBE_SIZE},  /* Bottom left */
        { CUBE_SIZE, -CUBE_SIZE,  CUBE_SIZE},  /* Bottom right */
        { CUBE_SIZE,  CUBE_SIZE,  CUBE_SIZE},  /* Top right */
        {-CUBE_SIZE,  CUBE_SIZE,  CUBE_SIZE},  /* Top left */
        
        /* Back face vertices */
        {-CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE},  /* Bottom left */
        { CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE},  /* Bottom right */
        { CUBE_SIZE,  CUBE_SIZE, -CUBE_SIZE},  /* Top right */
        {-CUBE_SIZE,  CUBE_SIZE, -CUBE_SIZE}   /* Top left */
    };
    
    /* Define indices for the six faces of the cube, each made of two triangles */
    int faces[6][4] = {
        {0, 1, 2, 3},  /* Front face */
        {1, 5, 6, 2},  /* Right face */
        {5, 4, 7, 6},  /* Back face */
        {4, 0, 3, 7},  /* Left face */
        {3, 2, 6, 7},  /* Top face */
        {4, 5, 1, 0}   /* Bottom face */
    };
    
    /* Draw the cube face by face */
    glBegin(GL_QUADS);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            int vertex = faces[i][j];
            glColor4fv(colors[vertex]);
            glVertex3fv(vertices[vertex]);
        }
    }
    glEnd();
}

/**
 * GLUT display callback
 */
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    /* Position the cube in view */
    glTranslatef(0.0f, 0.0f, -3.0f);
    
    /* Rotate slightly to see more than one face */
    glRotatef(25.0f, 1.0f, 0.0f, 0.0f);  /* Rotate around x-axis */
    glRotatef(30.0f, 0.0f, 1.0f, 0.0f);  /* Rotate around y-axis */
    
    drawCube();
    
    glutSwapBuffers();
}

/**
 * GLUT window reshape callback
 */
void reshape(int width, int height) {
    float aspect = (float)width / (float)height;
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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

/**
 * Initialize OpenGL settings
 */
void init(void) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  /* Dark background */
    
    /* Enable features */
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    /* Basic lighting */
    glEnable(GL_COLOR_MATERIAL);
}

int main(int argc, char** argv) {
    /* Initialize GLUT */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
    glutCreateWindow("3D Cube");
    
    /* Set up callbacks */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    /* Initialize OpenGL state */
    init();
    
    /* Enter main loop */
    glutMainLoop();
    return 0;
} 