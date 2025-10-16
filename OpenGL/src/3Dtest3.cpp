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

// ★追加: モデルデータをまとめて管理するための構造体
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

Model testModel; // ★修正: モデルデータを新しい構造体で管理

// --- 関数定義 ---

// ★修正: Model構造体にデータを読み込む関数
bool loadObjModel(Model& model, const std::string& filepath) {
    std::string warn, err;
    std::string base_dir = filepath.substr(0, filepath.find_last_of("/\\") + 1);
    model.loaded = tinyobj::LoadObj(&model.attrib, &model.shapes, &model.materials, &warn, &err, filepath.c_str(), base_dir.c_str());
    if (!warn.empty()) { std::cout << "WARN: " << warn << std::endl; }
    if (!err.empty()) { std::cerr << "ERR: " << err << std::endl; }
    if(model.loaded) { std::cout << "Successfully loaded model: " << filepath << std::endl; }
    return model.loaded;
}

// ★修正: ご要望通りの引数を持つ、汎用的な描画関数
void drawObjModel(const Model& model, float x, float y, float z, float scale, float rx, float ry, float rz) {
    if (!model.loaded) return;

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

bool loadTextureWithOpenCV(const char* filename) {
    cv::Mat image = cv::imread(filename); if (image.empty()) { printf("Error: Image not found: %s\n", filename); return false; }
    cv::cvtColor(image, image, cv::COLOR_BGR2RGB); cv::flip(image, image, 0);
    glGenTextures(1, &textureID); glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.cols, image.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, image.data);
    return true;
}

void renderBitmapString(float x, float y, float z, void* font, const char* string) { glRasterPos3f(x, y, z); for (const char* c = string; *c != '\0'; c++) { glutBitmapCharacter(font, *c); } }
void drawAxes() { glDisable(GL_LIGHTING); glDisable(GL_TEXTURE_2D); glLineWidth(3.0f); glColor3f(1.0f, 0.0f, 0.0f); glBegin(GL_LINES); glVertex3f(0.0f, 0.1f, 0.0f); glVertex3f(10.0f, 0.1f, 0.0f); glEnd(); renderBitmapString(10.5f, 0.1f, 0.0f, GLUT_BITMAP_HELVETICA_18, "X"); glColor3f(0.0f, 1.0f, 0.0f); glBegin(GL_LINES); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 10.0f, 0.0f); glEnd(); renderBitmapString(0.0f, 10.5f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Y"); glColor3f(0.0f, 0.0f, 1.0f); glBegin(GL_LINES); glVertex3f(0.0f, 0.1f, 0.0f); glVertex3f(0.0f, 0.1f, 10.0f); glEnd(); renderBitmapString(0.0f, 0.1f, 10.5f, GLUT_BITMAP_HELVETICA_18, "Z"); glLineWidth(1.0f); glEnable(GL_TEXTURE_2D); glEnable(GL_LIGHTING); }
void drawHUD() { glDisable(GL_LIGHTING); glDisable(GL_TEXTURE_2D); glDisable(GL_DEPTH_TEST); glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity(); gluOrtho2D(0.0, windowWidth, 0.0, windowHeight); glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity(); char coords[100]; sprintf(coords, "X: %.2f  Y: %.2f  Z: %.2f", cameraX, cameraY, cameraZ); glColor3f(0.0f, 0.0f, 0.0f); renderBitmapString(windowWidth - 270, windowHeight - 30, 0, GLUT_BITMAP_HELVETICA_18, coords); glPopMatrix(); glMatrixMode(GL_PROJECTION); glPopMatrix(); glMatrixMode(GL_MODELVIEW); glEnable(GL_DEPTH_TEST); glEnable(GL_TEXTURE_2D); glEnable(GL_LIGHTING); }
void drawGround() { GLfloat ground_mat[] = {1.0f, 1.0f, 1.0f, 1.0f}; glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ground_mat); glBindTexture(GL_TEXTURE_2D, textureID); glBegin(GL_QUADS); glNormal3f(0,1,0); glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0, 0.0, -50.0); glTexCoord2f(20.0f, 0.0f); glVertex3f( 50.0, 0.0, -50.0); glTexCoord2f(20.0f, 20.0f); glVertex3f( 50.0, 0.0, 50.0); glTexCoord2f(0.0f, 20.0f); glVertex3f(-50.0, 0.0, 50.0); glEnd(); }

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); glLoadIdentity();
    float lookX = cos(pitch) * cos(yaw); float lookY = sin(pitch); float lookZ = cos(pitch) * sin(yaw);
    gluLookAt(cameraX, cameraY, cameraZ, cameraX + lookX, cameraY + lookY, cameraZ + lookZ, 0.0f, 1.0f, 0.0f);
    
    drawGround();
    
    glPushAttrib(GL_LIGHTING_BIT);
    drawAxes();
    glPopAttrib();
    
    // ★修正: 新しい関数を使って、指定した位置・サイズでモデルを描画
    drawObjModel(testModel, 0.0f, 0.01f, 0.0f, 0.01f, 0.0f, 0.0f, 0.0f);

    drawHUD();
    
    glutSwapBuffers();
}

void update(int value) { float forwardX = cos(yaw); float forwardZ = sin(yaw); float rightX = -forwardZ; float rightZ = forwardX; float moveX = 0.0f, moveZ = 0.0f; if (keyStates['w']) { moveX += forwardX; moveZ += forwardZ; } if (keyStates['s']) { moveX -= forwardX; moveZ -= forwardZ; } if (keyStates['a']) { moveX -= rightX; moveZ -= rightZ; } if (keyStates['d']) { moveX += rightX; moveZ += rightZ; } float magnitude = sqrt(moveX * moveX + moveZ * moveZ); if (magnitude > 0) { moveX /= magnitude; moveZ /= magnitude; } cameraX += moveX * moveSpeed; cameraZ += moveZ * moveSpeed; bool onPlatform = (cameraX >= -50.0f && cameraX <= 50.0f && cameraZ >= -50.0f && cameraZ <= 50.0f); if (isJumping || !onPlatform) { verticalVelocity -= gravity; } cameraY += verticalVelocity; if (onPlatform && cameraY <= 1.7f) { cameraY = 1.7f; isJumping = false; verticalVelocity = 0.0f; } if (cameraY <= -50.0f) { cameraX = spawnX; cameraY = spawnY; cameraZ = spawnZ; isJumping = false; verticalVelocity = 0.0f; } glutPostRedisplay(); glutTimerFunc(16, update, 0); }
void keyboard(unsigned char key, int x, int y) { keyStates[tolower(key)] = true; switch (key) { case ' ': if (!isJumping) { isJumping = true; verticalVelocity = jumpSpeed; } break; case 27: exit(0); break; } }
void keyboardUp(unsigned char key, int x, int y) { keyStates[tolower(key)] = false; }
void mouseMotion(int x, int y) { if (firstMouse) { lastMouseX = x; lastMouseY = y; firstMouse = false; return; } float deltaX = (float)(x - lastMouseX); float deltaY = (float)(lastMouseY - y); lastMouseX = x; lastMouseY = y; yaw += deltaX * mouseSensitivity; pitch += deltaY * mouseSensitivity; if (pitch > M_PI_2 - 0.1f) pitch = M_PI_2 - 0.1f; if (pitch < -M_PI_2 + 0.1f) pitch = -M_PI_2 + 0.1f; if (x < 50 || x > windowWidth - 50 || y < 50 || y > windowHeight - 50) { lastMouseX = windowWidth / 2; lastMouseY = windowHeight / 2; glutWarpPointer(lastMouseX, lastMouseY); } }
void reshape(int w, int h) { windowWidth = w; windowHeight = h; glViewport(0, 0, w, h); glMatrixMode(GL_PROJECTION); glLoadIdentity(); gluPerspective(45.0, (double)w / (double)h, 0.1, 200.0); glMatrixMode(GL_MODELVIEW); }

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
    
    // ★修正: testModel にモデルを読み込む
    if(!loadObjModel(testModel, "../obj/test.obj")) {
        std::cerr << "Failed to load model" << std::endl;
    }
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
