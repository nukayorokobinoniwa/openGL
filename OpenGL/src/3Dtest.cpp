#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <random>

// --- 変数定義 ---
// カメラの位置
float cameraX = 0.0f, cameraY = 1.7f, cameraZ = 10.0f;

// カメラの向き
float yaw = -M_PI / 2.0f;
float pitch = 0.0f;

// マウスの最後の位置
int lastMouseX, lastMouseY;
bool firstMouse = true;

// 移動と視点感度
const float moveSpeed = 0.15f;
const float mouseSensitivity = 0.005f;

// ジャンプ関連
bool isJumping = false;
float jumpSpeed = 0.3f;
float verticalVelocity = 0.0f;
const float gravity = 0.015f;

// ウィンドウサイズ
int windowWidth = 800;
int windowHeight = 600;

// キーの状態を管理する配列
bool keyStates[256] = {false};

// ビルの構造体とリスト
struct Building {
    float x, z; 
    float width, depth, height; 
    GLfloat color[3]; 
};
std::vector<Building> buildings;


// --- 関数定義 ---

// ビルを描画する関数
void drawBuilding(float x, float z, float width, float depth, float height, GLfloat r, GLfloat g, GLfloat b) {
    glPushMatrix();
    glTranslatef(x, height / 2.0f, z);
    glScalef(width, height, depth);
    glColor3f(r, g, b);
    glutSolidCube(1.0);
    glPopMatrix();
}

// シーンを描画
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

    for (const auto& b : buildings) {
        drawBuilding(b.x, b.z, b.width, b.depth, b.height, b.color[0], b.color[1], b.color[2]);
    }

    glutSwapBuffers();
}

// 全体の更新処理
void update(int value) {
    float forwardX = cos(yaw);
    float forwardZ = sin(yaw);
    float rightX = -forwardZ;
    float rightZ = forwardX;

    float moveX = 0.0f;
    float moveZ = 0.0f;

    if (keyStates['w']) {
        moveX += forwardX;
        moveZ += forwardZ;
    }
    if (keyStates['s']) {
        moveX -= forwardX;
        moveZ -= forwardZ;
    }
    if (keyStates['a']) {
        moveX -= rightX;
        moveZ -= rightZ;
    }
    if (keyStates['d']) {
        moveX += rightX;
        moveZ += rightZ;
    }

    float magnitude = sqrt(moveX * moveX + moveZ * moveZ);
    if (magnitude > 0) {
        moveX = moveX / magnitude;
        moveZ = moveZ / magnitude;
    }
    
    cameraX += moveX * moveSpeed;
    cameraZ += moveZ * moveSpeed;
    
    if (isJumping) {
        cameraY += verticalVelocity;
        verticalVelocity -= gravity;
        if (cameraY <= 1.7f) {
            cameraY = 1.7f;
            isJumping = false;
            verticalVelocity = 0.0f;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// キーボードが押された時の処理
void keyboard(unsigned char key, int x, int y) {
    keyStates[key] = true;
    
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

// キーボードが離された時の処理
void keyboardUp(unsigned char key, int x, int y) {
    keyStates[key] = false;
}

// マウスの動きを検知
void mouseMotion(int x, int y) {
    if (firstMouse) {
        lastMouseX = x;
        lastMouseY = y;
        firstMouse = false;
        return;
    }
    
    float deltaX = (float)(x - lastMouseX);
    float deltaY = (float)(lastMouseY - y);

    lastMouseX = x;
    lastMouseY = y;

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

// ウィンドウリサイズ
void reshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 0.1, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

// 初期化
void initScene() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> disPos(-40.0, 40.0);
    std::uniform_real_distribution<> disSize(5.0, 20.0);
    std::uniform_real_distribution<> disWidthDepth(2.0, 10.0);

    for (int i = 0; i < 100; ++i) {
        Building b;
        b.x = disPos(gen); b.z = disPos(gen);
        b.width = disWidthDepth(gen); b.depth = disWidthDepth(gen);
        b.height = disSize(gen);
        float gray = (float)(rand() % 4 + 4) / 10.0f;
        b.color[0] = gray; b.color[1] = gray; b.color[2] = gray;
        buildings.push_back(b);
    }
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("3D City Walker");

    initScene();

    // 【重要】キーリピートを無効化し、キーを離した判定が正しく行われるようにする
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
