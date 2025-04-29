#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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
    srand(time(NULL));
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

    GLfloat light_position[] = {0.0f, 0.0f, 2.0f, 1.0f};
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
        glVertex3f(x, 0.0, z);
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
    glColor4f(1.0, 1.0, 0.0, 0.3 * pulse);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glutSolidSphere(1.5, slices, stacks);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
}

void drawButton(float x, float y, float width, float height, const char *label)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);

    // Draw button rectangle
    glColor3f(0.2f, 0.6f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    // Draw text
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(x + 10, y + 8);
    for (const char *c = label; *c; ++c)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glEnable(GL_LIGHTING);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
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
        t * (360.0 / 16.1) * speed};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0.0, 15.0, 25.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glRotated(viewRotationZ, 0.0, 0.0, 1.0);
    glRotated(viewRotationY, 0.0, 1.0, 0.0);

    drawStars();

    // Draw sun
    glColor3d(1, 1, 0);
    glutSolidSphere(1.0, slices, stacks);
    drawSunGlow();

    // Draw orbits and planets
    struct { double distance, size, r, g, b; } planets[] = {
        {2.0, 0.1, 0.5, 0.5, 0.5}, {3.0, 0.2, 1.0, 0.5, 0.0}, {4.0, 0.2, 0.0, 0.0, 1.0},
        {5.0, 0.15, 1.0, 0.0, 0.0}, {7.0, 0.5, 1.0, 0.5, 0.0}, {9.0, 0.4, 0.9, 0.8, 0.4},
        {11.0, 0.3, 0.0, 0.5, 1.0}, {13.0, 0.3, 0.0, 0.0, 0.5}
    };
    for (int i = 0; i < 8; i++) {
        glColor3d(1, 1, 1);
        drawOrbit(planets[i].distance);
        drawPlanet(planets[i].distance, planets[i].size, angles[i], planets[i].r, planets[i].g, planets[i].b);
    }

    // GUI buttons
    drawButton(20, 20, 100, 30, paused ? "Resume" : "Pause");
    drawButton(20, 60, 100, 30, "Zoom In");
    drawButton(20, 100, 100, 30, "Zoom Out");
    drawButton(20, 140, 100, 30, "Tilt Up");
    drawButton(20, 180, 100, 30, "Tilt Down");
    drawButton(20, 220, 100, 30, "Quit");

    glutSwapBuffers();
}

void mouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        int winHeight = glutGet(GLUT_WINDOW_HEIGHT);
        y = winHeight - y; // invert Y for GUI

        if (x >= 20 && x <= 120)
        {
            if (y >= 20 && y <= 50)
                paused = !paused;
            else if (y >= 60 && y <= 90)
                zoomFactor += zoomSpeed;
            else if (y >= 100 && y <= 130)
                zoomFactor = std::max(0.1, zoomFactor - zoomSpeed);
            else if (y >= 140 && y <= 170)
                viewRotationZ += 5.0;
            else if (y >= 180 && y <= 210)
                viewRotationZ -= 5.0;
            else if (y >= 220 && y <= 250)
                exit(0);
        }

        resize(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        glutPostRedisplay();
    }
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
        break;
    case '-':
        zoomFactor = std::max(0.1, zoomFactor - zoomSpeed);
        break;
    case 13:
        paused = !paused;
        break;
    }
    resize(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
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
        glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    initStarPositions();
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Solar System with GUI Controls");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouseClick);
    glutIdleFunc(idle);

    init();
    glutMainLoop();
    return 0;
}
