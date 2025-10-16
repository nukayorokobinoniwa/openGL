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

// 当たり判定用の構造体
struct BoundingBox {
    float minX, maxX, minY, maxY, minZ, maxZ;
};

// パレットの状態を管理するためのenum
enum PalletState {
    IDLE,    // 通常時
    TIPPING, // 転倒アニメーション中
    TIPPED   // 転倒済み
};

// パレットの情報を管理する構造体
struct Pallet {
    float x, y, z;
    float rotationX = 0.0f;
    float rotationY = 0.0f;
    float rotationZ = 0.0f;
    char interactionAxis = 'y';
    BoundingBox localBBox;
    PalletState state = IDLE;
    float visualY = 0.0f;
    float scale = 0.15f;
};

// --- 変数定義 ---
const float spawnX = 0.0f, spawnY = 2.2f, spawnZ = 10.0f;
float cameraX = spawnX, cameraY = spawnY, cameraZ = spawnZ;
float yaw = -M_PI / 2.0f;
float pitch = 0.0f;
int lastMouseX, lastMouseY;
bool firstMouse = true;
const float moveSpeed = 0.15f;
const float mouseSensitivity = 0.005f;
int windowWidth = 1600, windowHeight = 900;
bool keyStates[256] = {false};
bool justWarped = false;
bool isMouseLookActive = true;

GLuint groundTextureID;
GLuint wallTextureID;

float g_time = 0.0f;

Model testModel;
Model paletModel;
Model blenderModel;

std::vector<BoundingBox> wallColliders;
std::vector<Pallet> pallets;

// --- 関数定義 ---

/**
 * @brief モデルの頂点データからバウンディングボックスを計算する
 */
BoundingBox calculateModelBBox(const Model& model) {
    if (model.attrib.vertices.empty()) { return {0,0,0,0,0,0}; }
    float minX = model.attrib.vertices[0], maxX = model.attrib.vertices[0];
    float minY = model.attrib.vertices[1], maxY = model.attrib.vertices[1];
    float minZ = model.attrib.vertices[2], maxZ = model.attrib.vertices[2];
    for (size_t i = 0; i < model.attrib.vertices.size() / 3; ++i) {
        float x = model.attrib.vertices[3 * i + 0];
        float y = model.attrib.vertices[3 * i + 1];
        float z = model.attrib.vertices[3 * i + 2];
        if (x < minX) minX = x; if (x > maxX) maxX = x;
        if (y < minY) minY = y; if (y > maxY) maxY = y;
        if (z < minZ) minZ = z; if (z > maxZ) maxZ = z;
    }
    return {minX, maxX, minY, maxY, minZ, maxZ};
}

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
 * @brief .objファイルから読み込んだモデルを描画する
 */
void drawObjModel(const Model& model, float x, float y, float z, float scale, float rx, float ry, float rz) {
    if (!model.loaded) return;
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(ry, 0.0f, 1.0f, 0.0f);
    glRotatef(rx, 1.0f, 0.0f, 0.0f);
    glRotatef(rz, 0.0f, 0.0f, 1.0f);
    glScalef(scale, scale, scale);
    for (const auto& shape : model.shapes) {
        size_t index_offset = 0;
        for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++) {
            int fv = shape.mesh.num_face_vertices[f];
            int material_id = shape.mesh.material_ids[f];
            if (material_id < 0 || material_id >= model.materials.size()) {
                GLfloat default_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
                glMaterialfv(GL_FRONT, GL_DIFFUSE, default_diffuse);
            } else {
                const auto& mat = model.materials[material_id];
                glMaterialfv(GL_FRONT, GL_DIFFUSE, mat.diffuse);
                glMaterialfv(GL_FRONT, GL_AMBIENT, mat.ambient);
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
 * @brief OpenCVで画像ファイルを読み込む関数
 */
bool loadTexture(const char* filename, GLuint& textureID) {
    cv::Mat image = cv::imread(filename);
    if (image.empty()) {
        printf("Error: Image not found: %s\n", filename);
        return false;
    }
    cv::flip(image, image, 0);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image.cols, image.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, image.data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    printf("Successfully loaded texture: %s\n", filename);
    return true;
}

/**
 * @brief 3D空間にビットマップフォントの文字列を描画する
 */
void renderBitmapString(float x, float y, float z, void* font, const char* string) {
    glRasterPos3f(x, y, z);
    for (const char* c = string; *c != '\0'; c++) { glutBitmapCharacter(font, *c); }
}

/**
 * @brief ワールドの原点にXYZ座標軸を描画する
 */
void drawAxes() {
    glDisable(GL_LIGHTING); glDisable(GL_TEXTURE_2D); glLineWidth(3.0f);
    glColor3f(1.0f, 0.0f, 0.0f); glBegin(GL_LINES); glVertex3f(0.0f, 0.1f, 0.0f); glVertex3f(10.0f, 0.1f, 0.0f); glEnd();
    renderBitmapString(10.5f, 0.1f, 0.0f, GLUT_BITMAP_HELVETICA_18, "X");
    glColor3f(0.0f, 1.0f, 0.0f); glBegin(GL_LINES); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 10.0f, 0.0f); glEnd();
    renderBitmapString(0.0f, 10.5f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Y");
    glColor3f(0.0f, 0.0f, 1.0f); glBegin(GL_LINES); glVertex3f(0.0f, 0.1f, 0.0f); glVertex3f(0.0f, 0.1f, 10.0f); glEnd();
    renderBitmapString(0.0f, 0.1f, 10.5f, GLUT_BITMAP_HELVETICA_18, "Z");
    glLineWidth(1.0f); glEnable(GL_TEXTURE_2D); glEnable(GL_LIGHTING);
}

/**
 * @brief 画面にデバッグ情報などのHUD（2D情報）を描画する
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
 * @brief テクスチャ付きの地面を描画する
 */
void drawGround() {
    GLfloat ground_mat[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ground_mat);
    glBindTexture(GL_TEXTURE_2D, groundTextureID);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glNormal3f(0,1,0);
        glTexCoord2f(0.0f, 0.0f);   glVertex3f(-50.0, 0.0, -50.0);
        glTexCoord2f(20.0f, 0.0f);  glVertex3f( 50.0, 0.0, -50.0);
        glTexCoord2f(20.0f, 20.0f); glVertex3f( 50.0, 0.0,  50.0);
        glTexCoord2f(0.0f, 20.0f);  glVertex3f(-50.0, 0.0,  50.0);
    glEnd();
}

/**
 * @brief テクスチャ付きの壁を描画する
 */
void drawWalls() {
    GLfloat wall_mat[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wall_mat);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, wallTextureID);

    auto drawTexturedCube = [](float width, float height, float depth) {
        const float texRepeatScale = 1.0f;
        float texX = width * texRepeatScale;
        float texY = height * texRepeatScale;
        float texZ = depth * texRepeatScale;
        
        glColor3f(1.0f, 1.0f, 1.0f);

        glBegin(GL_QUADS);
        // Front Face
        glNormal3f(0.0, 0.0, 1.0);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
        glTexCoord2f(texX, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
        glTexCoord2f(texX, texY); glVertex3f(0.5f, 0.5f, 0.5f);
        glTexCoord2f(0.0f, texY); glVertex3f(-0.5f, 0.5f, 0.5f);
        // Back Face
        glNormal3f(0.0, 0.0, -1.0);
        glTexCoord2f(texX, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
        glTexCoord2f(texX, texY); glVertex3f(-0.5f, 0.5f, -0.5f);
        glTexCoord2f(0.0f, texY); glVertex3f(0.5f, 0.5f, -0.5f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
        // Top Face
        glNormal3f(0.0, 1.0, 0.0);
        glTexCoord2f(0.0f, texZ); glVertex3f(-0.5f, 0.5f, -0.5f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
        glTexCoord2f(texX, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);
        glTexCoord2f(texX, texZ); glVertex3f(0.5f, 0.5f, -0.5f);
        // Bottom Face
        glNormal3f(0.0, -1.0, 0.0);
        glTexCoord2f(texX, texZ); glVertex3f(-0.5f, -0.5f, -0.5f);
        glTexCoord2f(0.0f, texZ); glVertex3f(0.5f, -0.5f, -0.5f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
        glTexCoord2f(texX, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
        // Right face
        glNormal3f(1.0, 0.0, 0.0);
        glTexCoord2f(texZ, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
        glTexCoord2f(texZ, texY); glVertex3f(0.5f, 0.5f, -0.5f);
        glTexCoord2f(0.0f, texY); glVertex3f(0.5f, 0.5f, 0.5f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
        // Left Face
        glNormal3f(-1.0, 0.0, 0.0);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
        glTexCoord2f(texZ, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
        glTexCoord2f(texZ, texY); glVertex3f(-0.5f, 0.5f, 0.5f);
        glTexCoord2f(0.0f, texY); glVertex3f(-0.5f, 0.5f, -0.5f);
        glEnd();
    };

    auto drawWall = [&](float x, float z, float width, float depth, float height) {
        glPushMatrix();
        glTranslatef(x + width / 2.0f, height / 2.0f, z + depth / 2.0f);
        glScalef(width, height, depth);
        drawTexturedCube(width, height, depth);
        glPopMatrix();
    };

    float wall_height = 3.6f, wall_thick = 0.5f;
    drawWall(15.0f,-45.0f,10.0f,wall_thick,wall_height); drawWall(30.0f,-45.0f,10.0f,wall_thick,wall_height);
    drawWall(15.0f,-42.5f,wall_thick,5.0f,wall_height); drawWall(40.0f,-42.5f,wall_thick,5.0f,wall_height);
    drawWall(15.0f,-25.0f,10.0f,wall_thick,wall_height); drawWall(30.0f,-25.0f,10.0f,wall_thick,wall_height);
    drawWall(15.0f,-27.5f,wall_thick,5.0f,wall_height); drawWall(40.0f,-27.5f,wall_thick,5.0f,wall_height);
    drawWall(15.0f,-5.0f,30.0f,wall_thick,wall_height); drawWall(40.0f,0.0f,5.0f,wall_thick,wall_height);
    drawWall(15.0f,0.0f,20.0f,wall_thick,wall_height); drawWall(15.0f,5.0f,30.0f,wall_thick,wall_height);
    drawWall(-45.0f,35.0f,30.0f,wall_thick,wall_height); drawWall(-20.0f,40.0f,5.0f,wall_thick,wall_height);
    drawWall(-45.0f,40.0f,20.0f,wall_thick,wall_height); drawWall(-45.0f,45.0f,30.0f,wall_thick,wall_height);
}

/**
 * @brief 壁の当たり判定情報を生成する
 */
void setupColliders() {
    wallColliders.clear();
    auto addCollider = [](float x, float z, float width, float depth) {
        wallColliders.push_back({x, x + width, 0, 0, z, z + depth});
    };
    float wall_thick = 0.5f;
    addCollider(15.0f,-45.0f,10.0f,wall_thick); addCollider(30.0f,-45.0f,10.0f,wall_thick);
    addCollider(15.0f,-42.5f,wall_thick,5.0f); addCollider(40.0f,-42.5f,wall_thick,5.0f);
    addCollider(15.0f,-25.0f,10.0f,wall_thick); addCollider(30.0f,-25.0f,10.0f,wall_thick);
    addCollider(15.0f,-27.5f,wall_thick,5.0f); addCollider(40.0f,-27.5f,wall_thick,5.0f);
    addCollider(15.0f,-5.0f,30.0f,wall_thick); addCollider(40.0f,0.0f,5.0f,wall_thick);
    addCollider(15.0f,0.0f,20.0f,wall_thick); addCollider(15.0f,5.0f,30.0f,wall_thick);
    addCollider(-45.0f,35.0f,30.0f,wall_thick); addCollider(-20.0f,40.0f,5.0f,wall_thick);
    addCollider(-45.0f,40.0f,20.0f,wall_thick); addCollider(-45.0f,45.0f,30.0f,wall_thick);
}

/**
 * @brief パレットオブジェクトを初期化・配置する
 */
void setupPallets() {
    BoundingBox palletBaseBBox = calculateModelBBox(paletModel);
    const float x_scale_factor = 16.0f;
    const float y_scale_factor = 1.0f;
    const float z_scale_factor = 1.0f;
    palletBaseBBox.minX *= x_scale_factor;
    palletBaseBBox.maxX *= x_scale_factor;
    palletBaseBBox.minY *= y_scale_factor;
    palletBaseBBox.maxY *= y_scale_factor;
    palletBaseBBox.minZ *= z_scale_factor;
    palletBaseBBox.maxZ *= z_scale_factor;

    pallets.push_back({-17.0f, 1.8f, 39.6f, 0.0f, 90.0f, 0.0f, 'z', palletBaseBBox, IDLE, 1.8f, 0.15f});
    pallets.push_back({17.0f, 1.8f, -0.4f, 0.0f, 90.0f, 0.0f, 'z', palletBaseBBox, IDLE, 1.8f, 0.15f});
}

/**
 * @brief 毎フレームのメイン描画処理を行う
 */
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    float lookX = cos(pitch) * cos(yaw), lookY = sin(pitch), lookZ = cos(pitch) * sin(yaw);
    gluLookAt(cameraX, cameraY, cameraZ, cameraX + lookX, cameraY + lookY, cameraZ + lookZ, 0.0f, 1.0f, 0.0f);
    
    glEnable(GL_TEXTURE_2D);
    drawGround();
    drawWalls();

    drawAxes();
    drawObjModel(testModel, 0.0f, 0.01f, 0.0f, 0.01f, 0.0f, 0.0f, 0.0f);
    drawObjModel(blenderModel, -5.0f, 15.0f, -5.0f, 5.0f, 0.0f, 45.0f, 0.0f);
    for (const auto& pallet : pallets) {
        drawObjModel(paletModel, pallet.x, pallet.visualY, pallet.z, pallet.scale, pallet.rotationX, pallet.rotationY, pallet.rotationZ);
    }
    drawHUD();
    glutSwapBuffers();
}

/**
 * @brief パレットの状態（アニメーションなど）を更新する
 */
void updatePallets() {
    for (auto& pallet : pallets) {
        if (pallet.state == TIPPING) {
            bool animationDone = false;
            switch (pallet.interactionAxis) {
                case 'x': break;
                case 'y': break;
                case 'z':
                    if (pallet.rotationZ > -60.0f) {
                        pallet.rotationZ -= 1.0f;
                    } else {
                        pallet.rotationZ = -60.0f;
                        animationDone = true;
                    }
                    break;
            }
            if (animationDone) {
                pallet.state = TIPPED;
            }
        }
        pallet.visualY = pallet.y + sin(g_time * 4.0f) * 0.05f;
    }
}

/**
 * @brief 当たり判定をチェックするためのヘルパー関数
 */
bool checkCollision(float x, float z) {
    const float playerWidth = 0.2f;

    for (const auto& box : wallColliders) {
        if (x + playerWidth > box.minX && x - playerWidth < box.maxX &&
            z + playerWidth > box.minZ && z - playerWidth < box.maxZ) {
            return true;
        }
    }

    for (const auto& pallet : pallets) {
        if (pallet.state != IDLE) {
            float translatedX = x - pallet.x;
            float translatedZ = z - pallet.z;
            float angleRad = -pallet.rotationY * M_PI / 180.0f;
            float localX = translatedX * cos(angleRad) - translatedZ * sin(angleRad);
            float localZ = translatedX * sin(angleRad) + translatedZ * cos(angleRad);
            if (localX + playerWidth > pallet.localBBox.minX * pallet.scale && localX - playerWidth < pallet.localBBox.maxX * pallet.scale &&
                localZ + playerWidth > pallet.localBBox.minZ * pallet.scale && localZ - playerWidth < pallet.localBBox.maxZ * pallet.scale) {
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief タイマーで呼び出され、プレイヤーの位置やオブジェクトの状態を更新する
 */
void update(int value) {
    g_time += 1.0f / 60.0f;
    updatePallets();

    float forwardX = cos(yaw), forwardZ = sin(yaw), rightX = -forwardZ, rightZ = forwardX;
    float moveX = 0.0f, moveZ = 0.0f;
    if (keyStates['w']) { moveX += forwardX; moveZ += forwardZ; } if (keyStates['s']) { moveX -= forwardX; moveZ -= forwardZ; }
    if (keyStates['a']) { moveX -= rightX; moveZ -= rightZ; } if (keyStates['d']) { moveX += rightX; moveZ += rightZ; }
    
    float magnitude = sqrt(moveX * moveX + moveZ * moveZ);
    if (magnitude > 0) {
        moveX /= magnitude;
        moveZ /= magnitude;
    }
    
    float move_vec_x = moveX * moveSpeed;
    float move_vec_z = moveZ * moveSpeed;

    if (!checkCollision(cameraX + move_vec_x, cameraZ + move_vec_z)) {
        cameraX += move_vec_x;
        cameraZ += move_vec_z;
    } else {
        if (!checkCollision(cameraX + move_vec_x, cameraZ)) {
            cameraX += move_vec_x;
        }
        if (!checkCollision(cameraX, cameraZ + move_vec_z)) {
            cameraZ += move_vec_z;
        }
    }

    cameraY = spawnY;
    
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

/**
 * @brief キーが押されたときの処理を行うコールバック関数
 */
void keyboard(unsigned char key, int x, int y) {
    keyStates[tolower(key)] = true;
    switch (key) {
        case 27: exit(0); break;
        case ' ': {
            const float interactDistance = 3.0f;
            for (auto& pallet : pallets) {
                float dx = cameraX - pallet.x, dz = cameraZ - pallet.z;
                if (sqrt(dx*dx + dz*dz) < interactDistance) {
                    if (pallet.state == IDLE) {
                        pallet.z -= 2.5f;
                        pallet.state = TIPPING;
                        pallet.scale *= 1.5f;
                        break;
                    }
                }
            }
            break;
        }
    }
}

/**
 * @brief キーが離されたときの処理を行うコールバック関数
 */
void keyboardUp(unsigned char key, int x, int y) { keyStates[tolower(key)] = false; }

/**
 * @brief マウスが動いたときの処理を行うコールバック関数
 */
void mouseMotion(int x, int y) {
    if (!isMouseLookActive) {
        return;
    }

    if (justWarped) {
        justWarped = false;
        return;
    }

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

    if (pitch > M_PI_2 - 0.1f) {
        pitch = M_PI_2 - 0.1f;
    }
    if (pitch < -M_PI_2 + 0.1f) {
        pitch = -M_PI_2 + 0.1f;
    }

    // ▼▼▼ 端の判定を50pxから10pxに変更 ▼▼▼
    if (x < 10 || x > windowWidth - 10 || y < 10 || y > windowHeight - 10) {
        lastMouseX = windowWidth / 2;
        lastMouseY = windowHeight / 2;
        glutWarpPointer(lastMouseX, lastMouseY);
        justWarped = true;
    }
}

/**
 * @brief ウィンドウサイズが変更されたときの処理を行うコールバック関数
 */
void reshape(int w, int h) {
    windowWidth = w; windowHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 0.1, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

/**
 * @brief マウスがウィンドウ内に出入りした際の処理
 */
void entry(int state) {
    if (state == GLUT_ENTERED) {
        isMouseLookActive = true;
        firstMouse = true;
    } else if (state == GLUT_LEFT) {
        isMouseLookActive = false;
    }
}

void initScene() {
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat global_ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    GLfloat light_pos[] = { 5.0f, 10.0f, 5.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    
    if (!loadTexture("ground.jpg", groundTextureID)) { 
        printf("Failed to load ground texture.\n"); 
    }
    if (!loadTexture("wall.jpg", wallTextureID)) {
        printf("Failed to load wall texture.\n");
    }

    glEnable(GL_TEXTURE_2D);
    if(!loadObjModel(testModel, "../obj/test.obj")) { std::cerr << "Failed to load test.obj" << std::endl; }
    if(!loadObjModel(paletModel, "../obj/palet.obj")) { std::cerr << "Failed to load palet.obj" << std::endl; }
    if(!loadObjModel(blenderModel, "../obj/house.obj")) { std::cerr << "Failed to load house.obj" << std::endl; }
    setupColliders();
    setupPallets();
}

int main(int argc, char** argv) {
    setlocale(LC_NUMERIC, "C");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("3D FPS Controller - Edge Warp Fixed");
    initScene();
    glutIgnoreKeyRepeat(1);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(mouseMotion);
    glutSetCursor(GLUT_CURSOR_NONE);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutTimerFunc(0, update, 0);
    glutEntryFunc(entry);

    glutMainLoop();
    return 0;
}
