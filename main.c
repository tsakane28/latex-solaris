#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>  // Required for bool, true, false

static int slices = 50;
static int stacks = 50;
const int starCount = 1000;
static double star_positions[starCount][3];

double zoomFactor = 1.0;
const double zoomSpeed = 0.1;

double viewRotationY = 0.0;
double viewRotationZ = 0.0;

bool paused = false;

void initStarPositions()
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < starCount; ++i)
    {
        star_positions[i][0] = (rand() % 1000 - 500) / 10.0;
        star_positions[i][1] = (rand() % 1000 - 500) / 10.0;
        star_positions[i][2] = (rand() % 1000 - 500) / 10.0;
    }
}

void init()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat light_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light_position[] = {0.0f, 0.0f, 2.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

static void resize(int width, int height)
{
    const float aspect_ratio = (float)width / (float)height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0 / zoomFactor, aspect_ratio, 1.0, 100.0);
}

void drawOrbit(double radius)
{
    int segments = 100;
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++)
    {
        double angle = 2.0 * M_PI * i / segments;
        double x = radius * cos(angle);
        double z = radius * sin(angle);
        glVertex3f((float)x, 0.0f, (float)z);
    }
    glEnd();
}

void drawPlanet(double distance, double size, double angle, double r, double g, double b)
{
    glPushMatrix();
    glColor3d(r, g, b);
    glRotated(angle, 0, 1, 0);
    glTranslated(distance, 0.0, 0.0);
    glutSolidSphere(size, slices, stacks);
    glPopMatrix();
}

void drawStars()
{
    glDisable(GL_LIGHTING);
    glBegin(GL_POINTS);
    glColor3d(1.0, 1.0, 1.0);
    for (int i = 0; i < starCount; ++i)
    {
        glVertex3dv(star_positions[i]);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

void drawSunGlow()
{
    double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    double pulse = 0.5 + 0.4 * sin(0.5 * M_PI * t);

    glPushMatrix();
    glColor4f(1.0f, 1.0f, 0.0f, (float)(0.3 * pulse));
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glutSolidSphere(1.5, slices, stacks);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
}

static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double speed = 1.0;

    const double angles[] = {
        t * (360.0 / 60.0) * speed,
        t * (360.0 / 300.0) * speed,
        t * (360.0 / 24.0) * speed,
        t * (360.0 / 24.6) * speed,
        t * (360.0 / 9.9) * speed,
        t * (360.0 / 10.7) * speed,
        t * (360.0 / 17.2) * speed,
        t * (360.0 / 16.1) * speed
    };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0.0, 15.0, 25.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glRotated(viewRotationZ, 0.0, 0.0, 1.0);
    glRotated(viewRotationY, 0.0, 1.0, 0.0);

    drawStars();

    glPushMatrix();
    glColor3d(1, 1, 0);
    glutSolidSphere(1.0, slices, stacks);
    glPopMatrix();

    drawSunGlow();

    struct
    {
        double distance;
        double size;
        double r, g, b;
    } planets[] = {
        {2.0, 0.1, 0.5, 0.5, 0.5},
        {3.0, 0.2, 1.0, 0.5, 0.0},
        {4.0, 0.2, 0.0, 0.0, 1.0},
        {5.0, 0.15, 1.0, 0.0, 0.0},
        {7.0, 0.5, 1.0, 0.5, 0.0},
        {9.0, 0.4, 0.9, 0.8, 0.4},
        {11.0, 0.3, 0.0, 0.5, 1.0},
        {13.0, 0.3, 0.0, 0.0, 0.5}
    };

    for (int i = 0; i < 8; i++)
    {
        glColor3d(1, 1, 1);
        drawOrbit(planets[i].distance);
        drawPlanet(planets[i].distance, planets[i].size, angles[i], planets[i].r, planets[i].g, planets[i].b);
    }

    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
    case 'q':
        exit(0);
        break;
    case '+':
        zoomFactor += zoomSpeed;
        resize(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        break;
    case '-':
        zoomFactor -= zoomSpeed;
        if (zoomFactor < 0.1)
            zoomFactor = 0.1;
        resize(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        break;
    case 13:  // Enter
        paused = !paused;
        break;
    }
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        viewRotationY -= 5.0;
        break;
    case GLUT_KEY_RIGHT:
        viewRotationY += 5.0;
        break;
    case GLUT_KEY_UP:
        viewRotationZ += 5.0;
        break;
    case GLUT_KEY_DOWN:
        viewRotationZ -= 5.0;
        break;
    }
    glutPostRedisplay();
}

static void idle(void)
{
    if (!paused)
    {
        glutPostRedisplay();
    }
}

int main(int argc, char *argv[])
{
    initStarPositions();
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Z-Axis Rotation Demo - Solar System");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(specialKeys);
    glutIdleFunc(idle);

    init();
    glutMainLoop();
    return 0;
}
