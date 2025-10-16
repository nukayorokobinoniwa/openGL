#include <GL/glew.h>
#define FREEGLUT_STATIC
#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <cstdio>
#include <cctype>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <locale.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

// モデルデータをまとめて管理するための構造体
struct Model {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    bool loaded = false;
};

// --- 変数定義 ---
const float spawnX = 0.0f, spawnY = 1.7f, spawnZ = 10.0f;
float cameraX = spawnX, cameraY = spawnY, cameraZ = spawnZ;
float yaw = -M_PI / 2.0f;
float pitch = 0.0f;
int lastMouseX, lastMouseY;
bool firstMouse = true;
const float moveSpeed = 0.15f;
const float mouseSensitivity = 0.005f;
bool isJumping = false;
float jumpSpeed = 0.3f;
float verticalVelocity = 0.0f;
const float gravity = 0.015f;
int windowWidth = 800, windowHeight = 600;
bool keyStates[256] = {false};
GLuint textureID;

Model testModel;
Model paletModel;

// --- 関数定義 ---

/**
 * @brief tinyobjloaderを使い、.objと.mtlファイルを読み込んでModel構造体に格納する
 */
bool loadObjModel(Model& model, const std::string& filepath) {
    std::string warn, err;
    std::string base_dir = filepath.substr(0, filepath.find_last_of("/\\") + 1);
    model.loaded = tinyobj::LoadObj(&model.attrib, &model.shapes, &model.materials, &warn, &err, filepath.c_str(), base_dir.c_str());
    if (!warn.empty()) { std::cout << "WARN: " << warn << std::endl; }
    if (!err.empty()) { std::cerr << "ERR: " << err << std::endl; }
    if(model.loaded) { std::cout << "Successfully loaded model: " << filepath << std::endl; }
    return model.loaded;
}

/**
 * @brief .objモデルを指定された位置・サイズ・回転で描画する
 */
void drawObjModel(const Model& model, float x, float y, float z, float scale, float rx, float ry, float rz) {
    if (!model.loaded) {
        return;
    }
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(x, y, z); 
    glRotatef(rx, 1.0f, 0.0f, 0.0f);
    glRotatef(ry, 0.0f, 1.0f, 0.0f);
    glRotatef(rz, 0.0f, 0.0f, 1.0f);
    glScalef(scale, scale, scale);
    for (const auto& shape : model.shapes) {
        size_t index_offset = 0;
        for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++) {
            int fv = shape.mesh.num_face_vertices[f];
            int material_id = shape.mesh.material_ids[f];
            if (material_id < 0 || material_id >= model.materials.size()) {
                GLfloat default_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
                GLfloat default_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
                glMaterialfv(GL_FRONT, GL_DIFFUSE, default_diffuse);
                glMaterialfv(GL_FRONT, GL_AMBIENT, default_ambient);
            } else {
                const auto& mat = model.materials[material_id];
                glMaterialfv(GL_FRONT, GL_DIFFUSE, mat.diffuse);
                glMaterialfv(GL_FRONT, GL_AMBIENT, mat.ambient);
                glMaterialfv(GL_FRONT, GL_SPECULAR, mat.specular);
                glMaterialf(GL_FRONT, GL_SHININESS, mat.shininess);
            }
            glBegin(GL_TRIANGLES);
            for (size_t v = 0; v < fv; v++) {
                tinyobj::index_t idx = shape.mesh.indices[index_offset + v];
                if (idx.normal_index >= 0) {
                    glNormal3fv(&model.attrib.normals[3 * idx.normal_index]);
                }
                glVertex3fv(&model.attrib.vertices[3 * idx.vertex_index]);
            }
            glEnd();
            index_offset += fv;
        }
    }
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
}

/**
 * @brief OpenCVを使い、画像ファイルを読み込んでOpenGLテクスチャを作成する
 */
bool loadTextureWithOpenCV(const char* filename) {
    cv::Mat image = cv::imread(filename);
    if (image.empty()) {
        printf("Error: Image not found: %s\n", filename);
        return false;
    }
    cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
    cv::flip(image, image, 0);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.cols, image.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, image.data);
    return true;
}

/**
 * @brief 3D空間の指定した位置に2Dテキストを描画する
 */
void renderBitmapString(float x, float y, float z, void* font, const char* string) {
    glRasterPos3f(x, y, z);
    for (const char* c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

/**
 * @brief ワールドの原点にXYZの座標軸を描画する
 */
void drawAxes() {
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
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
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}

/**
 * @brief 画面右上にカメラ座標などのHUD（2D情報）を描画する
 */
void drawHUD() {
    glDisable(GL_LIGHTING); glDisable(GL_TEXTURE_2D); glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity(); gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
    glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity();
    char coords[100]; sprintf(coords, "X: %.2f  Y: %.2f  Z: %.2f", cameraX, cameraY, cameraZ);
    glColor3f(0.0f, 0.0f, 0.0f); renderBitmapString(windowWidth - 270, windowHeight - 30, 0, GLUT_BITMAP_HELVETICA_18, coords);
    glPopMatrix(); glMatrixMode(GL_PROJECTION); glPopMatrix();
    glMatrixMode(GL_MODELVIEW); glEnable(GL_DEPTH_TEST); glEnable(GL_TEXTURE_2D); glEnable(GL_LIGHTING);
}

/**
 * @brief Y=0の位置にテクスチャ付きの地面を描画する
 */
void drawGround() {
    GLfloat ground_mat[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ground_mat);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glBegin(GL_QUADS);
        glNormal3f(0,1,0);
        glTexCoord2f(0.0f, 0.0f);   glVertex3f(-50.0, 0.0, -50.0);
        glTexCoord2f(20.0f, 0.0f);  glVertex3f( 50.0, 0.0, -50.0);
        glTexCoord2f(20.0f, 20.0f); glVertex3f( 50.0, 0.0,  50.0);
        glTexCoord2f(0.0f, 20.0f);  glVertex3f(-50.0, 0.0,  50.0);
    glEnd();
}

/**
 * @brief 壁を描画する
 */
void drawWalls() {
    GLfloat wall_mat_diffuse[] = {0.8f, 0.7f, 0.6f, 1.0f}; // 壁の色
    GLfloat wall_mat_ambient[] = {0.4f, 0.35f, 0.3f, 1.0f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, wall_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_AMBIENT, wall_mat_ambient);
    glDisable(GL_TEXTURE_2D);

    // 壁を描画するヘルパー関数
    auto drawWall = [](float x, float z, float width, float depth, float height) {
        glPushMatrix();
        // x座標が左端になるように、中心を (x + width/2) にずらす
        glTranslatef(x + width / 2.0f, height / 2.0f, z);
        glScalef(width, height, depth);
        glutSolidCube(1.0);
        glPopMatrix();
    };

    // --- マップの壁を配置 (座標を再計算) ---
    float wall_height = 3.6f;
    float wall_thick = 0.5f;
    //左上の壁
    drawWall(15.0f, -45.0f, 10.0f, wall_thick, wall_height);
    drawWall(30.0f, -45.0f, 10.0f, wall_thick, wall_height);
    drawWall(15.0f, -42.5f, wall_thick, 5.0f, wall_height);
    drawWall(40.0f, -42.5f, wall_thick, 5.0f, wall_height);
    drawWall(15.0f, -25.0f, 10.0f, wall_thick, wall_height);
    drawWall(30.0f, -25.0f, 10.0f, wall_thick, wall_height);
    drawWall(15.0f, -27.5f, wall_thick, 5.0f, wall_height);
    drawWall(40.0f, -27.5f, wall_thick, 5.0f, wall_height);
    


    //真ん中右の壁
    drawWall(15.0f, -5.0f, 30.0f, wall_thick, wall_height);
    drawWall(40.0f, 0.0f, 5.0f, wall_thick, wall_height);
    drawWall(15.0f, 0.0f, 20.0f, wall_thick, wall_height);
    drawWall(15.0f, 5.0f, 30.0f, wall_thick, wall_height);
    //左下の壁
    drawWall(-45.0f, 35.0f, 30.0f, wall_thick, wall_height);
    drawWall(-20.0f, 40.0f, 5.0f, wall_thick, wall_height);
    drawWall(-45.0f, 40.0f, 20.0f, wall_thick, wall_height);
    drawWall(-45.0f, 45.0f, 30.0f, wall_thick, wall_height);

    glEnable(GL_TEXTURE_2D);
}


/**
 * @brief 毎フレーム呼ばれるメインの描画関数
 */
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    float lookX = cos(pitch) * cos(yaw); float lookY = sin(pitch); float lookZ = cos(pitch) * sin(yaw);
    gluLookAt(cameraX, cameraY, cameraZ, cameraX + lookX, cameraY + lookY, cameraZ + lookZ, 0.0f, 1.0f, 0.0f);
    
    drawGround();
    
    glPushAttrib(GL_LIGHTING_BIT);
    drawAxes();
    glPopAttrib();
    
    drawObjModel(testModel, 0.0f, 0.01f, 0.0f, 0.01f, 0.0f, 0.0f, 0.0f);
    drawObjModel(paletModel, -17.0f, 1.8f, 39.6f, 0.15f, 0.0f, 90.0f, 0.0f);

    drawWalls();

    drawHUD();
    
    glutSwapBuffers();
}

/**
 * @brief タイマーで定期的に呼ばれ、世界の物理状態（位置など）を更新する
 */
void update(int value) {
    float forwardX = cos(yaw); float forwardZ = sin(yaw); float rightX = -forwardZ; float rightZ = forwardX;
    float moveX = 0.0f, moveZ = 0.0f;

    if (keyStates['w']) { moveX += forwardX; moveZ += forwardZ; } if (keyStates['s']) { moveX -= forwardX; moveZ -= forwardZ; }
    if (keyStates['a']) { moveX -= rightX; moveZ -= rightZ; } if (keyStates['d']) { moveX += rightX; moveZ += rightZ; }
    
    float magnitude = sqrt(moveX * moveX + moveZ * moveZ);
    if (magnitude > 0) { moveX /= magnitude; moveZ /= magnitude; }
    
    cameraX += moveX * moveSpeed; cameraZ += moveZ * moveSpeed;
    
    bool onPlatform = (cameraX >= -50.0f && cameraX <= 50.0f && cameraZ >= -50.0f && cameraZ <= 50.0f);
    if (isJumping || !onPlatform) { verticalVelocity -= gravity; }
    cameraY += verticalVelocity;
    
    if (onPlatform && cameraY <= 1.7f) { cameraY = 1.7f; isJumping = false; verticalVelocity = 0.0f; }
    if (cameraY <= -50.0f) { cameraX = spawnX; cameraY = spawnY; cameraZ = spawnZ; isJumping = false; verticalVelocity = 0.0f; }
    
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

/**
 * @brief キーが押された時に呼ばれるコールバック関数
 */
void keyboard(unsigned char key, int x, int y) {
    keyStates[tolower(key)] = true;
    switch (key) {
        case ' ': if (!isJumping) { isJumping = true; verticalVelocity = jumpSpeed; } break;
        case 27: exit(0); break;
    }
}

/**
 * @brief キーが離された時に呼ばれるコールバック関数
 */
void keyboardUp(unsigned char key, int x, int y) { keyStates[tolower(key)] = false; }

/**
 * @brief マウスが動いた時に呼ばれるコールバック関数
 */
void mouseMotion(int x, int y) {
    if (firstMouse) { lastMouseX = x; lastMouseY = y; firstMouse = false; return; }
    float deltaX = (float)(x - lastMouseX); float deltaY = (float)(lastMouseY - y);
    lastMouseX = x; lastMouseY = y;
    yaw += deltaX * mouseSensitivity; pitch += deltaY * mouseSensitivity;
    if (pitch > M_PI_2 - 0.1f) { pitch = M_PI_2 - 0.1f; }
    if (pitch < -M_PI_2 + 0.1f) { pitch = -M_PI_2 + 0.1f; }
    if (x < 50 || x > windowWidth - 50 || y < 50 || y > windowHeight - 50) {
        lastMouseX = windowWidth / 2; lastMouseY = windowHeight / 2;
        glutWarpPointer(lastMouseX, lastMouseY);
    }
}

/**
 * @brief ウィンドウサイズが変更された時に呼ばれるコールバック関数
 */
void reshape(int w, int h) {
    windowWidth = w; windowHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 0.1, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

/**
 * @brief プログラム開始時に一度だけ呼ばれ、3D世界の初期設定を行う
 */
void initScene() {
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    GLfloat global_ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    
    GLfloat light_pos[] = { 5.0f, 10.0f, 5.0f, 1.0f };
    GLfloat light_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_spc[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_dif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_spc);
    
    if (!loadTextureWithOpenCV("test.jpg")) { printf("Failed to load texture.\n"); }
    glEnable(GL_TEXTURE_2D);
    
    if(!loadObjModel(testModel, "../obj/test.obj")) { std::cerr << "Failed to load test.obj" << std::endl; }
    if(!loadObjModel(paletModel, "../obj/palet.obj")) { std::cerr << "Failed to load palet.obj" << std::endl; }
}


int main(int argc, char** argv) {
    setlocale(LC_NUMERIC, "C");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("3D FPS Controller");
    
    GLenum err = glewInit();
    if (GLEW_OK != err) { fprintf(stderr, "Error: %s\n", glewGetErrorString(err)); return 1; }
    
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
