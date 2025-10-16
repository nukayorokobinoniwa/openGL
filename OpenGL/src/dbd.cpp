#include <GL/glut.h>
#include <cmath>

// 定数
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// カメラの位置
float cameraX = 0.0f, cameraY = 1.7f, cameraZ = 5.0f;

// カメラの向き（Y軸周りの回転: Yaw, X軸周りの回転: Pitch）
float yaw = -M_PI / 2.0f; // 初期状態で-Z方向を向く
float pitch = 0.0f;

// マウスの最後の位置
int lastMouseX, lastMouseY;
bool firstMouse = true;

// 移動と視点感度
const float moveSpeed = 0.1f;
const float mouseSensitivity = 0.005f;

// ジャンプ関連の値を調整
bool isJumping = false;
float jumpSpeed = 0.3f;       // ジャンプの初速を少し上げる
float verticalVelocity = 0.0f;
const float gravity = 0.015f; // 重力を少し強くして、フワフワしすぎないようにする

// ウィンドウサイズ
int windowWidth = 800;
int windowHeight = 600;

// 地面を描画
void drawGround() {
    glColor3f(0.3f, 0.7f, 0.3f); // 緑色
    glBegin(GL_QUADS);
        glVertex3f(-50.0f, 0.0f, -50.0f);
        glVertex3f(50.0f, 0.0f, -50.0f);
        glVertex3f(50.0f, 0.0f, 50.0f);
        glVertex3f(-50.0f, 0.0f, 50.0f);
    glEnd();
}

// オブジェクト（キューブ）を描画
void drawCube() {
    glColor3f(1.0f, 0.5f, 0.2f); // オレンジ色
    glutSolidCube(1.0);
}

// シーンを描画
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // カメラの向いている方向ベクトルを計算
    float lookX = cos(pitch) * cos(yaw);
    float lookY = sin(pitch);
    float lookZ = cos(pitch) * sin(yaw);

    // カメラの設定
    gluLookAt(cameraX, cameraY, cameraZ,                 // カメラの位置
              cameraX + lookX, cameraY + lookY, cameraZ + lookZ, // 注視点
              0.0f, 1.0f, 0.0f);                       // 上方向ベクトル

    drawGround();

    // いくつかキューブを配置
    glPushMatrix();
        glTranslatef(0.0f, 0.5f, 0.0f);
        drawCube();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-3.0f, 0.5f, -2.0f);
        drawCube();
    glPopMatrix();

    glutSwapBuffers();
}

// 全体の更新処理 (旧: updateJump)
void update(int value) {
    // ジャンプ処理
    if (isJumping) {
        // 1. 速度を位置に反映させる
        cameraY += verticalVelocity;
        // 2. 重力加速度を速度に反映させる
        verticalVelocity -= gravity;

        // 地面に着地したらジャンプを終了
        if (cameraY <= 1.7f) {
            cameraY = 1.7f;
            isJumping = false;
            verticalVelocity = 0.0f;
        }
    }

    // 再描画を要求
    glutPostRedisplay();
    
    // 次の更新を16ミリ秒後（約60FPS）に予約
    glutTimerFunc(16, update, 0);
}

// キーボード入力
void keyboard(unsigned char key, int x, int y) {
    // 前方ベクトル（水平方向のみ）
    float forwardX = cos(yaw);
    float forwardZ = sin(yaw);
    // 右方ベクトル
    float rightX = -forwardZ;
    float rightZ = forwardX;

    switch (key) {
        case 'w': // 前進
            cameraX += forwardX * moveSpeed;
            cameraZ += forwardZ * moveSpeed;
            break;
        case 's': // 後退
            cameraX -= forwardX * moveSpeed;
            cameraZ -= forwardZ * moveSpeed;
            break;
        case 'a': // 左へ平行移動
            cameraX -= rightX * moveSpeed;
            cameraZ -= rightZ * moveSpeed;
            break;
        case 'd': // 右へ平行移動
            cameraX += rightX * moveSpeed;
            cameraZ += rightZ * moveSpeed;
            break;
        case ' ': // ジャンプ
            if (!isJumping) {
                isJumping = true;
                verticalVelocity = jumpSpeed;
            }
            break;
        case 27: // ESCキーで終了
            exit(0);
    }
    // glutPostRedisplay(); // update関数で呼ばれるのでここでは不要
}

// マウスの動きを検知
void mouseMotion(int x, int y) {
    if (firstMouse) {
        lastMouseX = x;
        lastMouseY = y;
        firstMouse = false;
        return;
    }
    
    // マウスの移動量を計算
    float deltaX = (float)(x - lastMouseX);
    float deltaY = (float)(lastMouseY - y); // Yは上がマイナスなので逆

    lastMouseX = x;
    lastMouseY = y;

    // YawとPitchを更新
    yaw += deltaX * mouseSensitivity;
    pitch += deltaY * mouseSensitivity;

    // Pitch（上下の視点移動）に制限をかける
    if (pitch > M_PI / 2.0f - 0.01f) {
        pitch = M_PI / 2.0f - 0.01f;
    }
    if (pitch < -M_PI / 2.0f + 0.01f) {
        pitch = -M_PI / 2.0f + 0.01f;
    }

    // 画面の端に行かないようにマウスカーソルを中央に戻す
    if (x < 50 || x > windowWidth - 50 || y < 50 || y > windowHeight - 50) {
        lastMouseX = windowWidth / 2;
        lastMouseY = windowHeight / 2;
        glutWarpPointer(lastMouseX, lastMouseY);
    }

    // glutPostRedisplay(); // update関数で呼ばれるのでここでは不要
}

// ウィンドウのリサイズ時に呼ばれる
void reshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// 初期化
void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
}

// メイン関数
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("3D FPS Control");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(mouseMotion); // マウスが動いた時に呼び出す関数を登録
    glutSetCursor(GLUT_CURSOR_NONE);    // マウスカーソルを非表示にする
    
    // glutIdleFunc(updateJump); を削除し、代わりにTimerFuncを開始
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}
