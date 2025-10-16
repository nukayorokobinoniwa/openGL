#include <GL/glut.h>

#ifdef _MSC_VER
#define _USE_MATH_DEFINES
#endif
#include <math.h>

void drawCircleOutline(double x, double y, double radius, int segments) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++) {
        double angle = 2.0 * M_PI * i / segments;
        glVertex2d(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    double radius = 0.1;
    int segments = 100;

    // 青い輪
    glColor3d(0.0, 0.0, 1.0);
    drawCircleOutline(-0.3*4, 0.1*4, radius * 7, segments);

    // 黒い輪
    glColor3d(0.0, 0.0, 0.0);
    drawCircleOutline(0.0, 0.1*4, radius * 7, segments);

    // 赤い輪
    glColor3d(1.0, 0.0, 0.0);
    drawCircleOutline(0.3*4, 0.1*4, radius * 7, segments);

    // 黄色い輪
    glColor3d(1.0, 1.0, 0.0);
    drawCircleOutline(-0.15*4, -0.05*4, radius * 7, segments);

    // 緑の輪
    glColor3d(0.0, 1.0, 0.0);
    drawCircleOutline(0.15*4, -0.05*4, radius * 7, segments);

    glFlush();
}

void resize(int w, int h) {
    glViewport(0, 0, w, h);
    glLoadIdentity();
    glOrtho(-w / 200.0, w / 200.0, -h / 200.0, h / 200.0, -1.0, 1.0);
}

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

int main(int argc, char *argv[]) {
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow("Olympic Flag");
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    init();
    glutMainLoop();
    return 0;
}
