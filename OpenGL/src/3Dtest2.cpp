#define FREEGLUT_STATIC
#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <random>
#include <cstdio>
#include <cctype> // tolower() を使用するために追加

// --- 変数定義 ---
const float spawnX = 0.0f;
const float spawnY = 1.7f;
const float spawnZ = 10.0f;
float cameraX = spawnX, cameraY = spawnY, cameraZ = spawnZ;
float yaw = -M_PI / 2.0f;
float pitch = 0.0f;
int lastMouseX, lastMouseY;
bool firstMouse = true;
const float moveSpeed = 0.15f;
const float sprintSpeed = 0.30f;
const float mouseSensitivity = 0.005f;
bool isJumping = false;
float jumpSpeed = 0.3f;
float verticalVelocity = 0.0f;
const float gravity = 0.015f;
int windowWidth = 800;
int windowHeight = 600;
bool keyStates[256] = {false};


// --- 関数定義 ---

void renderBitmapString(float x, float y, float z, void* font, const char* string) {
    glRasterPos3f(x, y, z);
    for (const char* c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void drawAxes() {
    glLineWidth(3.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES); glVertex3f(0.0f, 0.1f, 0.0f); glVertex3f(10.0f, 0.1f, 0.0f); glEnd();
    renderBitmapString(10.5f, 0.1f, 0.0f, GLUT_BITMAP_HELVETICA_18, "X");
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 10.0f, 0.0f); glEnd();
    renderBitmapString(0.0f, 10.5f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Y");
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES); glVertex3f(0.0f, 0.1f, 0.0f); glVertex3f(0.0f, 0.1f, 10.0f); glEnd();
    renderBitmapString(0.0f, 0.1f, 10.5f, GLUT_BITMAP_HELVETICA_18, "Z");
    glLineWidth(1.0f);
}

void drawHUD() {
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    char coords[100];
    sprintf(coords, "X: %.2f  Y: %.2f  Z: %.2f", cameraX, cameraY, cameraZ);
    glColor3f(0.0f, 0.0f, 0.0f);
    renderBitmapString(windowWidth - 270, windowHeight - 30, 0, GLUT_BITMAP_HELVETICA_18, coords);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    float lookX = cos(pitch) * cos(yaw);
    float lookY = sin(pitch);
    float lookZ = cos(pitch) * sin(yaw);
    gluLookAt(cameraX, cameraY, cameraZ,
              cameraX + lookX, cameraY + lookY, cameraZ + lookZ,
              0.0f, 1.0f, 0.0f);
    glColor3f(0.3f, 0.7f, 0.3f);
    glBegin(GL_QUADS);
        glVertex3f(-50.0, 0.0,  50.0);
        glVertex3f( 50.0, 0.0,  50.0);
        glVertex3f( 50.0, 0.0, -50.0);
        glVertex3f(-50.0, 0.0, -50.0);
    glEnd();
    drawAxes();
    drawHUD();
    glutSwapBuffers();
}

void update(int value) {
    // --- 水平移動 ---
    float forwardX = cos(yaw);
    float forwardZ = sin(yaw);
    float rightX = -forwardZ;
    float rightZ = forwardX;
    float moveX = 0.0f, moveZ = 0.0f;
    if (keyStates['w']) { moveX += forwardX; moveZ += forwardZ; }
    if (keyStates['s']) { moveX -= forwardX; moveZ -= forwardZ; }
    if (keyStates['a']) { moveX -= rightX;   moveZ -= rightZ;   }
    if (keyStates['d']) { moveX += rightX;   moveZ += rightZ;   }
    float magnitude = sqrt(moveX * moveX + moveZ * moveZ);
    if (magnitude > 0) { moveX /= magnitude; moveZ /= magnitude; }
    
    float currentSpeed = moveSpeed;
    if (glutGetModifiers() & GLUT_ACTIVE_SHIFT) {
        currentSpeed = sprintSpeed;
    }
    
    cameraX += moveX * currentSpeed;
    cameraZ += moveZ * currentSpeed;
    
    // --- 垂直移動 ---
    bool onPlatform = (cameraX >= -50.0f && cameraX <= 50.0f && cameraZ >= -50.0f && cameraZ <= 50.0f);
    if (isJumping || !onPlatform) {
        verticalVelocity -= gravity;
    }
    cameraY += verticalVelocity;
    if (onPlatform && cameraY <= 1.7f) {
        cameraY = 1.7f;
        isJumping = false;
        verticalVelocity = 0.0f;
    }
    if (cameraY <= -50.0f) {
        cameraX = spawnX; cameraY = spawnY; cameraZ = spawnZ;
        isJumping = false; verticalVelocity = 0.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// 【修正】キーボードが押された時の処理
void keyboard(unsigned char key, int x, int y) {
    // 受け取ったキーを小文字に変換してから状態を保存
    keyStates[tolower(key)] = true; 
    
    switch (key) {
        case ' ':
            if (!isJumping) {
                isJumping = true;
                verticalVelocity = jumpSpeed;
            }
            break;
        case 27:
            exit(0);
            break;
    }
}

// 【修正】キーボードが離された時の処理
void keyboardUp(unsigned char key, int x, int y) {
    // 受け取ったキーを小文字に変換してから状態をリセット
    keyStates[tolower(key)] = false;
}


void mouseMotion(int x, int y) {
    if (firstMouse) { lastMouseX = x; lastMouseY = y; firstMouse = false; return; }
    float deltaX = (float)(x - lastMouseX);
    float deltaY = (float)(lastMouseY - y);
    lastMouseX = x; lastMouseY = y;
    yaw += deltaX * mouseSensitivity;
    pitch += deltaY * mouseSensitivity;
    if (pitch > M_PI_2 - 0.1f) pitch = M_PI_2 - 0.1f;
    if (pitch < -M_PI_2 + 0.1f) pitch = -M_PI_2 + 0.1f;
    if (x < 50 || x > windowWidth - 50 || y < 50 || y > windowHeight - 50) {
        lastMouseX = windowWidth / 2;
        lastMouseY = windowHeight / 2;
        glutWarpPointer(lastMouseX, lastMouseY);
    }
}

void reshape(int w, int h) {
    windowWidth = w; windowHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 0.1, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

void initScene() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("3D FPS Controller");
    initScene();
    glutIgnoreKeyRepeat(1); 
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(mouseMotion);
    glutSetCursor(GLUT_CURSOR_NONE);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp); 
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}
