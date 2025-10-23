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
#include <random>
#include <algorithm>
#include <numeric>
#include <limits>
#include <cstring> 

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

// 乱数生成器
std::mt19937 rng(std::random_device{}());

// 3Dベクトル用の構造体
struct Vec3 {
    float x, y, z;
};

/**
 * @brief 2つの3Dベクトルの外積を計算する。
 * @param a 1つ目のベクトル
 * @param b 2つ目のベクトル
 * @return 2つのベクトルの外積ベクトル
 */
Vec3 cross(const Vec3& a, const Vec3& b) {
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

/**
 * @brief 2つの3Dベクトルの内積を計算する。
 * @param a 1つ目のベクトル
 * @param b 2つ目のベクトル
 * @return 2つのベクトルの内積
 */
float dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

/**
 * @brief 3Dベクトルを正規化する（長さを1にする）。
 * @param v 正規化するベクトル
 * @return 正規化されたベクトル
 */
Vec3 normalize(const Vec3& v) {
    float len = std::sqrt(dot(v, v));
    if (len > 0) {
        return {v.x / len, v.y / len, v.z / len};
    }
    return v;
}

/**
 * @brief 透視投影行列を作成する。
 * @param mat 結果を格納する16要素のfloat配列
 * @param fovY Y方向の視野角 (度数法)
 * @param aspect アスペクト比 (幅 / 高さ)
 * @param zNear 前方クリッピング面までの距離
 * @param zFar 後方クリッピング面までの距離
 */
void perspectiveMatrix(float* mat, float fovY, float aspect, float zNear, float zFar) {
    memset(mat, 0, 16 * sizeof(float));
    float f = 1.0f / tanf(fovY * (M_PI / 180.0f) / 2.0f);
    mat[0] = f / aspect;
    mat[5] = f;
    mat[10] = (zFar + zNear) / (zNear - zFar);
    mat[11] = -1.0f;
    mat[14] = (2.0f * zFar * zNear) / (zNear - zFar);
}

/**
 * @brief ビュー行列（カメラの位置と向き）を作成する。
 * @param mat 結果を格納する16要素のfloat配列
 * @param eye カメラの位置ベクトル
 * @param center カメラの注視点の位置ベクトル
 * @param up カメラの上方向を示すベクトル
 */
void lookAtMatrix(float* mat, const Vec3& eye, const Vec3& center, const Vec3& up) {
    Vec3 f = normalize({center.x - eye.x, center.y - eye.y, center.z - eye.z});
    Vec3 s = normalize(cross(f, up));
    Vec3 u = cross(s, f);

    mat[0] = s.x;
    mat[4] = s.y;
    mat[8] = s.z;
    mat[12] = -dot(s, eye);

    mat[1] = u.x;
    mat[5] = u.y;
    mat[9] = u.z;
    mat[13] = -dot(u, eye);

    mat[2] = -f.x;
    mat[6] = -f.y;
    mat[10] = -f.z;
    mat[14] = dot(f, eye);

    mat[3] = 0.0f;
    mat[7] = 0.0f;
    mat[11] = 0.0f;
    mat[15] = 1.0f;
}

/**
 * @brief テクスチャマッピング可能な球体を描画する。
 * @param radius 球の半径
 * @param slices 経度方向の分割数
 * @param stacks 緯度方向の分割数
 */
void drawTexturedSphere(GLdouble radius, GLint slices, GLint stacks) {
    for (int i = 0; i < stacks; ++i) {
        GLdouble lat0 = M_PI * (-0.5 + (double)i / stacks);
        GLdouble z0 = radius * sin(lat0);
        GLdouble zr0 = radius * cos(lat0);
        GLdouble lat1 = M_PI * (-0.5 + (double)(i + 1) / stacks);
        GLdouble z1 = radius * sin(lat1);
        GLdouble zr1 = radius * cos(lat1);
        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; ++j) {
            GLdouble lng = 2 * M_PI * (double)j / slices;
            GLdouble x = cos(lng);
            GLdouble y = sin(lng);
            glNormal3d(x * zr1, y * zr1, z1);
            glTexCoord2d((double)j / slices, (double)(i + 1) / stacks);
            glVertex3d(x * zr1, y * zr1, z1);
            glNormal3d(x * zr0, y * zr0, z0);
            glTexCoord2d((double)j / slices, (double)i / stacks);
            glVertex3d(x * zr0, y * zr0, z0);
        }
        glEnd();
    }
}


// Perlin Noise用のヘルパー関数
/**
 * @brief パーリンノイズで滑らかな補間を行うためのフェード関数。
 * @param t 入力値 (通常0.0～1.0)
 * @return 補間された値
 */
float fade(float t) { return t * t * t * (t * (t * 6 - 15) + 10); }

/**
 * @brief 線形補間を行う。
 * @param a 開始値
 * @param b 終了値
 * @param t 補間係数 (0.0～1.0)
 * @return 補間された値
 */
float linearInterpolate(float a, float b, float t) { return a + t * (b - a); }

/**
 * @brief ハッシュ値に基づいて勾配ベクトルを計算する。
 * @param hash ハッシュ値
 * @param x x座標
 * @param y y座標
 * @param z z座標
 * @return 勾配ベクトルの計算結果
 */
float grad(int hash, float x, float y, float z) {
    int h = hash & 15;
    float u = h < 8 ? x : y;
    float v = h < 4 ? y : (h == 12 || h == 14 ? x : z);
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}
int p[512]; // Permutation table

/**
 * @brief パーリンノイズ生成器を初期化する。ランダムな置換テーブルを作成する。
 */
void initPerlinNoise() {
    std::iota(p, p + 256, 0);
    std::shuffle(p, p + 256, rng);
    for (int i = 0; i < 256; ++i) {
        p[i + 256] = p[i];
    }
}

/**
 * @brief 3次元パーリンノイズを生成する。
 * @param x x座標
 * @param y y座標
 * @param z z座標
 * @return 0.0から1.0の範囲のノイズ値
 */
float perlinNoise(float x, float y, float z) {
    int X = (int)floor(x) & 255;
    int Y = (int)floor(y) & 255;
    int Z = (int)floor(z) & 255;
    x -= floor(x);
    y -= floor(y);
    z -= floor(z);
    float u = fade(x), v = fade(y), w = fade(z);
    int A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z;
    int B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;
    float res = linearInterpolate(
        linearInterpolate(
            linearInterpolate(grad(p[AA], x, y, z), grad(p[BA], x - 1, y, z), u),
            linearInterpolate(grad(p[AB], x, y - 1, z), grad(p[BB], x - 1, y - 1, z), u), v),
        linearInterpolate(
            linearInterpolate(grad(p[AA + 1], x, y, z - 1), grad(p[BA + 1], x - 1, y, z - 1), u),
            linearInterpolate(grad(p[AB + 1], x, y - 1, z - 1), grad(p[BB + 1], x - 1, y - 1, z - 1), u), v), w);
    return (res + 1.0f) / 2.0f;
}

// モデルデータをまとめて管理するための構造体
struct Model {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    bool loaded = false;
};

// 当たり判定用の構造体 (AABB)
struct BoundingBox {
    float minX, maxX, minY, maxY, minZ, maxZ;
};

// 2Dベクトル用の構造体
struct Vec2 {
    float x, z;
};

// 回転を考慮した当たり判定用の構造体 (OBB)
struct OBB {
    float cx, cz;
    float halfWidth, halfDepth;
    float angle;
};

// パレットの状態を管理するためのenum
enum PalletState { IDLE, TIPPING, TIPPED };

// パレットの情報を管理する構造体
struct Pallet {
    float x, y, z;
    float rotationX = 0.0f, rotationY = 0.0f, rotationZ = 0.0f;
    char interactionAxis = 'y';
    BoundingBox localBBox;
    PalletState state = IDLE;
    float visualY = 0.0f;
    float scale = 0.15f;
    bool collisionAdded = false;
};

// 落ちる葉っぱの構造体
struct Leaf {
    float x, y, z;
    float vx, vy, vz;
    float rotationAngleX, rotationAngleY, rotationAngleZ;
    float rotationSpeedX, rotationSpeedY, rotationSpeedZ;
    float scale;
    float lifeTime;
    float maxLifeTime;
    GLfloat color[4];
    GLuint textureID;
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
bool showColliders = false;

GLuint groundTextureID, wallTextureID, leafTextureID, rockTextureID;
float g_time = 0.0f;
Model paletModel, blenderModel;
std::vector<BoundingBox> wallColliders;
std::vector<OBB> obbColliders;
std::vector<Pallet> pallets;
std::vector<Leaf> fallingLeaves;
const float treeX = 0.0f, treeY = 0.0f, treeZ = 0.0f;
const float treeLeafSpawnRadius = 3.0f, treeLeafSpawnHeightOffset = 5.0f;
const float playerRadius = 0.2f;

// Vec2のヘルパー関数
Vec2 operator+(const Vec2& a, const Vec2& b) { return {a.x + b.x, a.z + b.z}; }
Vec2 operator-(const Vec2& a, const Vec2& b) { return {a.x - b.x, a.z - b.z}; }
Vec2 operator*(const Vec2& v, float s) { return {v.x * s, v.z * s}; }
Vec2 operator/(const Vec2& v, float s) { return {v.x / s, v.z / s}; }
float dot(const Vec2& v1, const Vec2& v2) { return v1.x * v2.x + v1.z * v2.z; }
float lengthSq(const Vec2& v) { return dot(v, v); }
float length(const Vec2& v) { return std::sqrt(lengthSq(v)); }

/**
 * @brief OBB（有向境界ボックス）の4つの頂点座標を計算する。
 * @param obb 頂点を計算するOBB
 * @return 4つの頂点(Vec2)のベクター
 */
std::vector<Vec2> getOBBVertices(const OBB& obb) {
    std::vector<Vec2> vertices(4);
    float cosA = cosf(obb.angle);
    float sinA = sinf(obb.angle);
    Vec2 center = {obb.cx, obb.cz};

    Vec2 axisX = {cosA, sinA};
    Vec2 axisZ = {-sinA, cosA};
    Vec2 halfVecX = axisX * obb.halfWidth;
    Vec2 halfVecZ = axisZ * obb.halfDepth;

    vertices[0] = center - halfVecX - halfVecZ;
    vertices[1] = center + halfVecX - halfVecZ;
    vertices[2] = center + halfVecX + halfVecZ;
    vertices[3] = center - halfVecX + halfVecZ;

    return vertices;
}

/**
 * @brief ポリゴンの頂点を指定された軸に射影し、最小値と最大値を見つける。
 * @param vertices ポリゴンの頂点のベクター
 * @param axis 射影する軸
 * @param min 射影の最小値を格納する参照
 * @param max 射影の最大値を格納する参照
 */
void projectPolygon(const std::vector<Vec2>& vertices, const Vec2& axis, float& min, float& max) {
    min = std::numeric_limits<float>::max();
    max = std::numeric_limits<float>::lowest();
    for (const auto& v : vertices) {
        float p = dot(v, axis);
        if (p < min) min = p;
        if (p > max) max = p;
    }
}

/**
 * @brief モデルの頂点データからAABB（軸並行境界ボックス）を計算する。
 * @param model バウンディングボックスを計算するモデル
 * @return 計算されたBoundingBox構造体
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
 * @brief .objファイルから3Dモデルを読み込む。
 * @param model 読み込んだモデルデータを格納するModel構造体への参照
 * @param filepath モデルファイルのパス
 * @return 読み込みが成功したかどうか (true/false)
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
 * @brief 読み込んだ.objモデルを描画する。
 * @param model 描画するModel構造体
 * @param x ワールド座標X
 * @param y ワールド座標Y
 * @param z ワールド座標Z
 * @param scale モデルのスケール
 * @param rx X軸周りの回転角度
 * @param ry Y軸周りの回転角度
 * @param rz Z軸周りの回転角度
 * @param emissionColor 発光マテリアルの色。nullptrの場合は発光しない。
 */
void drawObjModel(const Model& model, float x, float y, float z, float scale, float rx, float ry, float rz, const GLfloat* emissionColor = nullptr) {
    if (!model.loaded) return;
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();

    if (emissionColor != nullptr) {
        glMaterialfv(GL_FRONT, GL_EMISSION, emissionColor);
    }

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
    
    if (emissionColor != nullptr) {
        GLfloat no_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
        glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);
    }

    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
}

/**
 * @brief OpenCVを使用して画像ファイルを読み込み、OpenGLテクスチャとして生成する。
 * @param filename テクスチャとして使用する画像ファイルのパス
 * @param textureID 生成されたテクスチャのIDを格納する変数への参照
 * @param alpha アルファチャンネル（透明度）を持つ画像として読み込むか
 * @return 読み込みが成功したかどうか (true/false)
 */
bool loadTexture(const char* filename, GLuint& textureID, bool alpha = false) {
    cv::Mat image = cv::imread(filename, alpha ? cv::IMREAD_UNCHANGED : cv::IMREAD_COLOR);
    if (image.empty()) {
        printf("Error: Image not found: %s\n", filename);
        return false;
    }
    cv::flip(image, image, 0);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    if (alpha) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.cols, image.rows, 0, GL_BGRA, GL_UNSIGNED_BYTE, image.data);
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.cols, image.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, image.data);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    printf("Successfully loaded texture: %s (alpha: %s)\n", filename, alpha ? "true" : "false");
    return true;
}

/**
 * @brief 画面上の指定した3D座標にビットマップフォントで文字列を描画する。
 * @param x 文字列を描画するX座標
 * @param y 文字列を描画するY座標
 * @param z 文字列を描画するZ座標
 * @param font 使用するGLUTフォント
 * @param string 描画する文字列
 */
void renderBitmapString(float x, float y, float z, void* font, const char* string) {
    glRasterPos3f(x, y, z);
    for (const char* c = string; *c != '\0'; c++) { glutBitmapCharacter(font, *c); }
}

/**
 * @brief XYZ座標軸をデバッグ用に描画する。
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
 * @brief 画面の右上にHUD（ヘッドアップディスプレイ）としてカメラ座標を表示する。
 */
void drawHUD() {
    glDisable(GL_LIGHTING); glDisable(GL_TEXTURE_2D); glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity(); 
    glOrtho(0.0, windowWidth, 0.0, windowHeight, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity();
    char coords[100]; sprintf(coords, "X: %.2f  Y: %.2f  Z: %.2f", cameraX, cameraY, cameraZ);
    glColor3f(1.0f, 1.0f, 1.0f);
    renderBitmapString(windowWidth - 270, windowHeight - 30, 0, GLUT_BITMAP_HELVETICA_18, coords);
    glPopMatrix(); glMatrixMode(GL_PROJECTION); glPopMatrix();
    glMatrixMode(GL_MODELVIEW); glEnable(GL_DEPTH_TEST); glEnable(GL_TEXTURE_2D); glEnable(GL_LIGHTING);
}

/**
 * @brief 地面を描画する。
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
 * @brief ステージの壁を描画する。
 */
void drawWalls() {
    GLfloat wall_mat[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wall_mat);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, wallTextureID);

    // テクスチャ付きの立方体を描画するヘルパーラムダ関数
    auto drawTexturedCube = [](float width, float height, float depth) {
        const float texRepeatScale = 1.0f;
        float texX = width * texRepeatScale;
        float texY = height * texRepeatScale;
        float texZ = depth * texRepeatScale;
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_QUADS);
        glNormal3f(0.0, 0.0, 1.0);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
        glTexCoord2f(texX, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
        glTexCoord2f(texX, texY); glVertex3f(0.5f, 0.5f, 0.5f);
        glTexCoord2f(0.0f, texY); glVertex3f(-0.5f, 0.5f, 0.5f);
        glNormal3f(0.0, 0.0, -1.0);
        glTexCoord2f(texX, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
        glTexCoord2f(texX, texY); glVertex3f(-0.5f, 0.5f, -0.5f);
        glTexCoord2f(0.0f, texY); glVertex3f(0.5f, 0.5f, -0.5f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
        glNormal3f(0.0, 1.0, 0.0);
        glTexCoord2f(0.0f, texZ); glVertex3f(-0.5f, 0.5f, -0.5f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
        glTexCoord2f(texX, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);
        glTexCoord2f(texX, texZ); glVertex3f(0.5f, 0.5f, -0.5f);
        glNormal3f(0.0, -1.0, 0.0);
        glTexCoord2f(texX, texZ); glVertex3f(-0.5f, -0.5f, -0.5f);
        glTexCoord2f(0.0f, texZ); glVertex3f(0.5f, -0.5f, -0.5f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
        glTexCoord2f(texX, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
        glNormal3f(1.0, 0.0, 0.0);
        glTexCoord2f(texZ, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
        glTexCoord2f(texZ, texY); glVertex3f(0.5f, 0.5f, -0.5f);
        glTexCoord2f(0.0f, texY); glVertex3f(0.5f, 0.5f, 0.5f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
        glNormal3f(-1.0, 0.0, 0.0);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
        glTexCoord2f(texZ, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
        glTexCoord2f(texZ, texY); glVertex3f(-0.5f, 0.5f, 0.5f);
        glTexCoord2f(0.0f, texY); glVertex3f(-0.5f, 0.5f, -0.5f);
        glEnd();
    };

    // 壁のセグメントを描画するヘルパーラムダ関数
    auto drawWallSegment = [&](float x, float y, float z, float width, float depth, float height, float rx, float ry, float rz) {
        glPushMatrix();
        glTranslatef(x + width / 2.0f, y + height / 2.0f, z + depth / 2.0f);
        glRotatef(ry, 0.0f, 1.0f, 0.0f);
        glRotatef(rx, 1.0f, 0.0f, 0.0f);
        glRotatef(rz, 0.0f, 0.0f, 1.0f);
        glScalef(width, height, depth);
        drawTexturedCube(width, height, depth);
        glPopMatrix();
    };

    // Y軸方向に伸びる壁のセグメントを描画するヘルパーラムダ関数
    auto drawWallSegmentY = [&](float x, float y, float z, float width, float depth, float height, float rx, float ry, float rz) {
        glPushMatrix();
        glTranslatef(x + depth / 2.0f, y + height / 2.0f, z + width / 2.0f);
        glRotatef(ry, 0.0f, 1.0f, 0.0f);
        glRotatef(rx, 1.0f, 0.0f, 0.0f);
        glRotatef(rz, 0.0f, 0.0f, 1.0f);
        glScalef(depth, height, width);
        drawTexturedCube(depth, height, width);
        glPopMatrix();
    };

    // drawWallSegmentのラッパー
    auto drawWall = [&](float x, float z, float width, float depth, float height, float rx, float ry, float rz) {
        drawWallSegment(x, 0.0f, z, width, depth, height, rx, ry, rz);
    };

    // 窓のある壁を描画するヘルパーラムダ関数
    auto drawWindowWalls = [&](float x, float z, float width, float depth, float height, float rx, float ry, float rz) {
        const float windowWidthRatio = 0.4f;
        const float windowHeightRatio = 0.4f;
        float windowWidth = width * windowWidthRatio;
        float windowHeight = height * windowHeightRatio;
        float marginWidth = (width - windowWidth) / 2.0f;
        float marginHeight = (height - windowHeight) / 2.0f;

        drawWallSegment(x, 0.0f, z, width, depth, marginHeight, rx, ry, rz);
        float topY = marginHeight + windowHeight;
        drawWallSegment(x, topY, z, width, depth, marginHeight, rx, ry, rz);
        drawWallSegment(x, marginHeight, z, marginWidth, depth, windowHeight, rx, ry, rz);
        float rightX = x + marginWidth + windowWidth;
        drawWallSegment(rightX, marginHeight, z, marginWidth, depth, windowHeight, rx, ry, rz);
    };

    // Y軸方向に伸びる窓のある壁を描画するヘルパーラムダ関数
    auto drawWindowWallY = [&](float x, float z, float width, float depth, float height, float rx, float ry, float rz) {
        const float windowWidthRatio = 0.4f;
        const float windowHeightRatio = 0.4f;
        float windowWidth = width * windowWidthRatio;
        float windowHeight = height * windowHeightRatio;
        float marginWidth = (width - windowWidth) / 2.0f;
        float marginHeight = (height - windowHeight) / 2.0f;

        drawWallSegmentY(x, 0.0f, z, width, depth, marginHeight, rx, ry, rz);
        float topY = marginHeight + windowHeight;
        drawWallSegmentY(x, topY, z, width, depth, marginHeight, rx, ry, rz);
        drawWallSegmentY(x, marginHeight, z, marginWidth, depth, windowHeight, rx, ry, rz);
        float rightZ = z + marginWidth + windowWidth;
        drawWallSegmentY(x, marginHeight, rightZ, marginWidth, depth, windowHeight, rx, ry, rz);
    };

    // 分割された壁を描画するヘルパーラムダ関数
    auto drawDividedWall = [&](float x, float z, float width, float depth, float height, float rx, float ry, float rz) {
        const float dividerThickness = 0.5f; 
        float sideWallWidth = (width - dividerThickness) / 2.0f;
        drawWallSegment(x, 0.0f, z, sideWallWidth, depth, height, rx, ry, rz); 
        float dividerX = x + sideWallWidth;
        drawWallSegment(dividerX, 0.0f, z, dividerThickness, depth, height, rx, ry, rz); 
        float rightWallX = dividerX + dividerThickness;
        drawWallSegment(rightWallX, 0.0f, z, sideWallWidth, depth, height, rx, ry, rz); 
    };

    float wall_height = 3.6f, wall_thick = 0.5f;
    
    drawWall(15.0f,-45.0f,10.0f,wall_thick,wall_height, 0.0f, 0.0f, 0.0f);
    drawWall(30.0f,-45.0f,10.0f,wall_thick,wall_height, 0.0f, 0.0f, 0.0f);
    drawWall(15.0f,-45.0f,wall_thick,5.0f,wall_height, 0.0f, 0.0f, 0.0f);
    drawWall(40.0f,-45.0f,wall_thick,5.0f,wall_height, 0.0f, 0.0f, 0.0f);
    drawWall(15.0f,-25.0f,10.0f,wall_thick,wall_height, 0.0f, 0.0f, 0.0f);
    drawWall(30.0f,-25.0f,10.0f,wall_thick,wall_height, 0.0f, 0.0f, 0.0f);
    drawWall(15.0f,-30.0f,wall_thick,5.0f,wall_height, 0.0f, 0.0f, 0.0f);
    drawWall(40.0f,-30.0f,wall_thick,5.0f,wall_height, 0.0f, 0.0f, 0.0f);
    drawWall(15.0f,-5.0f,30.0f,wall_thick,wall_height, 0.0f, 0.0f, 0.0f);
    drawWall(40.0f,0.0f,5.0f,wall_thick,wall_height, 0.0f, 0.0f, 0.0f);
    drawWall(15.0f,0.0f,20.0f,wall_thick,wall_height, 0.0f, 0.0f, 0.0f);
    drawWall(15.0f,5.0f,30.0f,wall_thick,wall_height, 0.0f, 0.0f, 0.0f);
    drawWall(-45.0f,35.0f,30.0f,wall_thick,wall_height, 0.0f, 0.0f, 0.0f);
    drawWall(-20.0f,40.0f,5.0f,wall_thick,wall_height, 0.0f, 0.0f, 0.0f);
    drawWall(-45.0f,40.0f,20.0f,wall_thick,wall_height, 0.0f, 0.0f, 0.0f);
    drawWall(-45.0f,45.0f,30.0f,wall_thick,wall_height, 0.0f, 0.0f, 0.0f);
    drawWall(10.0f,-41.0f,wall_thick,3.0f,wall_height, 0.0f, 0.0f, 0.0f);
    drawWall(-10.0f,-31.0f,wall_thick,3.0f,wall_height, 0.0f, 0.0f, 0.0f);
    
    drawWall(-30.0f, 2.0f, 15.0f, wall_thick, wall_height, 0.0f, -45.0f, 0.0f);
    drawWall(-40.0f, -2.0f, 15.0f, wall_thick, wall_height, 0.0f, -45.0f, 0.0f);

    drawWindowWallY(-10.0f, 35.0f, 10.0f, wall_thick, wall_height, 0.0f, 0.0f, 0.0f);
    drawWindowWalls(-10.0f, -30.0f, 10.0f, wall_thick, wall_height, 0.0f, 0.0f, 0.0f);
    drawWindowWalls(0.0f, -40.0f, 10.0f, wall_thick, wall_height, 0.0f, 0.0f, 0.0f);
}

/**
 * @brief 円柱を描画する。
 * @param radius 円柱の半径
 * @param height 円柱の高さ
 * @param sides 円柱の側面を構成するポリゴンの数
 * @param baseHeight 円柱の底面のY座標
 */
void drawCylinder(float radius, float height, int sides, float baseHeight = 0.0f) {
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= sides; i++) {
        float angle = 2.0f * M_PI * i / sides;
        float x = cos(angle);
        float z = sin(angle);
        glNormal3f(x, 0.0f, z);
        glVertex3f(x * radius, baseHeight + height, z * radius);
        glVertex3f(x * radius, baseHeight, z * radius);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, baseHeight + height, 0.0f);
    for (int i = 0; i <= sides; i++) {
        float angle = 2.0f * M_PI * i / sides;
        glVertex3f(cos(angle) * radius, baseHeight + height, sin(angle) * radius);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, baseHeight, 0.0f);
    for (int i = sides; i >= 0; i--) {
        float angle = 2.0f * M_PI * i / sides;
        glVertex3f(cos(angle) * radius, baseHeight, sin(angle) * radius);
    }
    glEnd();
}

/**
 * @brief 木を描画する。（幹は円柱、葉は円錐で表現）
 */
void drawTree() {
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(treeX, treeY, treeZ);

    GLfloat trunk_mat[] = {0.5f, 0.3f, 0.1f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, trunk_mat);
    drawCylinder(0.8f, 5.0f, 20, 0.0f);

    GLfloat leaves_mat[] = {0.0f, 0.7f, 0.2f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, leaves_mat);

    glPushMatrix();
        glTranslatef(0.0f, 5.0f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glutSolidCone(3.0f, 4.0f, 20, 10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, 7.0f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glutSolidCone(2.5f, 3.5f, 20, 10);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0.0f, 9.0f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glutSolidCone(2.0f, 3.0f, 20, 10);
    glPopMatrix();

    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
}

/**
 * @brief 落下する葉のパーティクルを描画する。
 */
void drawFallingLeaves() {
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glAlphaFunc(GL_GREATER, 0.01f);
    glEnable(GL_ALPHA_TEST);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, leafTextureID);

    for (const auto& leaf : fallingLeaves) {
        glColor4fv(leaf.color);
        glPushMatrix();
        glTranslatef(leaf.x, leaf.y, leaf.z);
        
        GLfloat modelview[16];
        glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
        glRotatef(atan2(modelview[0], modelview[2]) * 180.0f / M_PI, 0.0f, 1.0f, 0.0f);
        
        glRotatef(leaf.rotationAngleX, 1.0f, 0.0f, 0.0f);
        glRotatef(leaf.rotationAngleY, 0.0f, 1.0f, 0.0f);
        glRotatef(leaf.rotationAngleZ, 0.0f, 0.0f, 1.0f);

        float halfSize = leaf.scale / 2.0f;
        
        glBegin(GL_QUADS);
            glNormal3f(0.0f, 0.0f, 1.0f);

            glTexCoord2f(0.0f, 0.0f); 
            glVertex3f(-halfSize, -halfSize, 0.0f);

            glTexCoord2f(1.0f, 0.0f); 
            glVertex3f( halfSize, -halfSize, 0.0f);

            glTexCoord2f(1.0f, 1.0f); 
            glVertex3f( halfSize * 0.7f,  halfSize, 0.0f);

            glTexCoord2f(0.0f, 1.0f); 
            glVertex3f(-halfSize * 0.7f,  halfSize, 0.0f);
        glEnd();
        glPopMatrix();
    }

    glDisable(GL_ALPHA_TEST);
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}

/**
 * @brief 岩（テクスチャ付きの球体）を描画する。
 * @param x ワールド座標X
 * @param y ワールド座標Y
 * @param z ワールド座標Z
 * @param radius 岩の半径
 */
void drawRock(float x, float y, float z, float radius) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, rockTextureID);

    glPushMatrix();
    glTranslatef(x, y, z);

    GLfloat rock_mat[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rock_mat);
    
    drawTexturedSphere(radius, 32, 32);
    
    glPopMatrix();
}

/**
 * @brief デバッグ用に当たり判定（AABBとOBB）をワイヤーフレームで描画する。
 */
void drawColliders() {
    if (!showColliders) return;

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glLineWidth(2.0f);
    const float wall_height = 3.6f;

    // AABBを緑色で描画
    glColor3f(0.0f, 1.0f, 0.0f);
    for (const auto& box : wallColliders) {
        glBegin(GL_LINE_LOOP);
            glVertex3f(box.minX, 0.01f, box.minZ);
            glVertex3f(box.maxX, 0.01f, box.minZ);
            glVertex3f(box.maxX, 0.01f, box.maxZ);
            glVertex3f(box.minX, 0.01f, box.maxZ);
        glEnd();
        glBegin(GL_LINE_LOOP);
            glVertex3f(box.minX, wall_height, box.minZ);
            glVertex3f(box.maxX, wall_height, box.minZ);
            glVertex3f(box.maxX, wall_height, box.maxZ);
            glVertex3f(box.minX, wall_height, box.maxZ);
        glEnd();
        glBegin(GL_LINES);
            glVertex3f(box.minX, 0.01f, box.minZ); glVertex3f(box.minX, wall_height, box.minZ);
            glVertex3f(box.maxX, 0.01f, box.minZ); glVertex3f(box.maxX, wall_height, box.minZ);
            glVertex3f(box.maxX, 0.01f, box.maxZ); glVertex3f(box.maxX, wall_height, box.maxZ);
            glVertex3f(box.minX, 0.01f, box.maxZ); glVertex3f(box.minX, wall_height, box.maxZ);
        glEnd();
    }

    // OBBを赤色で描画
    glColor3f(1.0f, 0.0f, 0.0f);
    for (const auto& obb : obbColliders) {
        std::vector<Vec2> vertices = getOBBVertices(obb);
        glBegin(GL_LINE_LOOP);
            glVertex3f(vertices[0].x, 0.01f, vertices[0].z);
            glVertex3f(vertices[1].x, 0.01f, vertices[1].z);
            glVertex3f(vertices[2].x, 0.01f, vertices[2].z);
            glVertex3f(vertices[3].x, 0.01f, vertices[3].z);
        glEnd();
        glBegin(GL_LINE_LOOP);
            glVertex3f(vertices[0].x, wall_height, vertices[0].z);
            glVertex3f(vertices[1].x, wall_height, vertices[1].z);
            glVertex3f(vertices[2].x, wall_height, vertices[2].z);
            glVertex3f(vertices[3].x, wall_height, vertices[3].z);
        glEnd();
        glBegin(GL_LINES);
            glVertex3f(vertices[0].x, 0.01f, vertices[0].z); glVertex3f(vertices[0].x, wall_height, vertices[0].z);
            glVertex3f(vertices[1].x, 0.01f, vertices[1].z); glVertex3f(vertices[1].x, wall_height, vertices[1].z);
            glVertex3f(vertices[2].x, 0.01f, vertices[2].z); glVertex3f(vertices[2].x, wall_height, vertices[2].z);
            glVertex3f(vertices[3].x, 0.01f, vertices[3].z); glVertex3f(vertices[3].x, wall_height, vertices[3].z);
        glEnd();
    }
    
    // プレイヤーの円形当たり判定をシアンで描画
    glColor3f(0.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(cameraX, 0.01f, cameraZ);
    glBegin(GL_LINE_LOOP);
    for(int i=0; i<360; i++) {
        float degInRad = i*M_PI/180;
        glVertex3f(cos(degInRad)*playerRadius, 0.0f, sin(degInRad)*playerRadius);
    }
    glEnd();
    glPopMatrix();


    glLineWidth(1.0f);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}

/**
 * @brief 壁やオブジェクトの当たり判定をセットアップする。
 */
void setupColliders() {
    wallColliders.clear();
    obbColliders.clear();

    auto addCollider = [](float x, float z, float width, float depth) {
        wallColliders.push_back({x, x + width, 0.0f, 3.6f, z, z + depth});
    };
    
    float wall_thick = 0.5f;
    addCollider(15.0f,-45.0f,10.0f,wall_thick); addCollider(30.0f,-45.0f,10.0f,wall_thick);
    addCollider(15.0f,-45.0f,wall_thick,5.0f); addCollider(40.0f,-45.0f,wall_thick,5.0f);
    addCollider(15.0f,-25.0f,10.0f,wall_thick); addCollider(30.0f,-25.0f,10.0f,wall_thick);
    addCollider(15.0f,-30.0f,wall_thick,5.0f); addCollider(40.0f,-30.0f,wall_thick,5.0f);
    addCollider(15.0f,-5.0f,30.0f,wall_thick); addCollider(40.0f,0.0f,5.0f,wall_thick);
    addCollider(15.0f,0.0f,20.0f,wall_thick); addCollider(15.0f,5.0f,30.0f,wall_thick);
    addCollider(-45.0f,35.0f,30.0f,wall_thick); addCollider(-20.0f,40.0f,5.0f,wall_thick);
    addCollider(-45.0f,40.0f,20.0f,wall_thick); addCollider(-45.0f,45.0f,30.0f,wall_thick);
    addCollider(10.0f,-41.0f,wall_thick,3.0f); 
    addCollider(-10.0f,-31.0f,wall_thick,3.0f); 

    float angle_rad = 45.0f * M_PI / 180.0f;
    float w = 15.0f;
    float d = wall_thick;
    
    obbColliders.push_back({ -30.0f + (w / 2.0f), 2.0f + (d / 2.0f), w / 2.0f, d / 2.0f, angle_rad });
    obbColliders.push_back({ -40.0f + (w / 2.0f), -2.0f + (d / 2.0f), w / 2.0f, d / 2.0f, angle_rad });
    
    { 
        float wall_width_z = 10.0f;
        float wall_depth_x = wall_thick;
        const float windowWidthRatio = 0.4f;
        float windowWidth = wall_width_z * windowWidthRatio;
        float marginWidth = (wall_width_z - windowWidth) / 2.0f;
        float startX = -10.0f;
        float startZ = 35.0f;
        addCollider(startX, startZ, wall_depth_x, marginWidth);
        float rightZ = startZ + marginWidth + windowWidth;
        addCollider(startX, rightZ, wall_depth_x, marginWidth);
    }

    { 
        float wall_width_x = 10.0f;
        float wall_depth_z = wall_thick;
        const float windowWidthRatio = 0.4f;
        float windowWidth = wall_width_x * windowWidthRatio;
        float marginWidth = (wall_width_x - windowWidth) / 2.0f;
        float startX = -10.0f;
        float startZ = -30.0f;
        addCollider(startX, startZ, marginWidth, wall_depth_z);
        float rightX = startX + marginWidth + windowWidth;
        addCollider(rightX, startZ, marginWidth, wall_depth_z);
    }

    { 
        float wall_width_x = 10.0f;
        float wall_depth_z = wall_thick;
        const float windowWidthRatio = 0.4f;
        float windowWidth = wall_width_x * windowWidthRatio;
        float marginWidth = (wall_width_x - windowWidth) / 2.0f;
        float startX = 0.0f;
        float startZ = -40.0f;
        addCollider(startX, startZ, marginWidth, wall_depth_z);
        float rightX = startX + marginWidth + windowWidth;
        addCollider(rightX, startZ, marginWidth, wall_depth_z);
    }

    float groundEdge = 50.0f;
    float boundaryWidth = 100.0f;
    addCollider(-groundEdge, -groundEdge - wall_thick, boundaryWidth, wall_thick);
    addCollider(-groundEdge, groundEdge, boundaryWidth, wall_thick);
    addCollider(-groundEdge - wall_thick, -groundEdge, wall_thick, boundaryWidth);
    addCollider(groundEdge, -groundEdge, wall_thick, boundaryWidth);

    float rockRadius = 5.0f;
    float rockX = -35.0f;
    float rockZ = -35.0f;
    wallColliders.push_back({rockX - rockRadius, rockX + rockRadius, 0, 0, rockZ - rockRadius, rockZ + rockRadius});
}

/**
 * @brief パレットオブジェクトを初期位置にセットアップする。
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

    pallets.push_back({-17.0f, 1.8f, 39.6f, 0.0f, 90.0f, 0.0f, 'z', palletBaseBBox, IDLE, 1.8f, 0.15f, false});
    pallets.push_back({17.0f, 1.8f, -0.4f, 0.0f, 90.0f, 0.0f, 'z', palletBaseBBox, IDLE, 1.8f, 0.15f, false});
}

/**
 * @brief メインの描画関数。glutDisplayFuncに登録される。
 */
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    float lookX = cos(pitch) * cos(yaw);
    float lookY = sin(pitch);
    float lookZ = cos(pitch) * sin(yaw);
    float lookAtMat[16];
    lookAtMatrix(lookAtMat, {cameraX, cameraY, cameraZ}, {cameraX + lookX, cameraY + lookY, cameraZ + lookZ}, {0.0f, 1.0f, 0.0f});
    glMultMatrixf(lookAtMat);
    
    glEnable(GL_TEXTURE_2D);
    drawGround();
    drawWalls();
    drawTree();
    // drawAxes(); // 軸の表示を無効化
    drawObjModel(blenderModel, 30.0f, 3.0f, 30.0f, 3.0f, 0.0f, 180.0f, 0.0f);
    
    for (const auto& pallet : pallets) {
        float emission_intensity = (sin(g_time * 4.0f) + 1.0f) / 2.0f;
        GLfloat pallet_emission[] = {
            emission_intensity * 0.8f, 
            emission_intensity * 0.8f, 
            emission_intensity * 0.5f, 
            1.0f
        };
        drawObjModel(paletModel, pallet.x, pallet.visualY, pallet.z, pallet.scale, pallet.rotationX, pallet.rotationY, pallet.rotationZ, pallet_emission);
    }

    drawFallingLeaves();
    drawRock(-35.0f, 0.0f, -35.0f, 5.0f); 

    drawColliders();

    drawHUD();
    glutSwapBuffers();
}

/**
 * @brief パレットの状態（アニメーション、当たり判定追加など）を更新する。
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

        if (pallet.state == TIPPED && !pallet.collisionAdded) {
            float halfWidth = (pallet.localBBox.maxX - pallet.localBBox.minX) * pallet.scale / 2.0f;
            float halfDepth = (pallet.localBBox.maxZ - pallet.localBBox.minZ) * pallet.scale / 2.0f;
            
            float angle_rad = pallet.rotationY * M_PI / 180.0f;
            
            OBB newCollider;
            newCollider.cx = pallet.x;
            newCollider.cz = pallet.z;
            newCollider.halfWidth = halfWidth;
            newCollider.halfDepth = halfDepth;
            newCollider.angle = angle_rad;
            
            obbColliders.push_back(newCollider);
            
            pallet.collisionAdded = true;

            std::cout << "Added OBB collider for tipped pallet." << std::endl;
        }

        pallet.visualY = pallet.y + sin(g_time * 4.0f) * 0.05f;
    }
}

/**
 * @brief 新しい葉パーティクルを生成する。
 * @param treeCenterY 木の中心Y座標
 */
void spawnLeaf(float treeCenterY) {
    std::uniform_real_distribution<float> distAngle(0.0f, 2.0f * M_PI);
    std::uniform_real_distribution<float> distRadius(0.0f, treeLeafSpawnRadius);
    std::uniform_real_distribution<float> distHeightOffset(0.0f, 3.0f);
    std::uniform_real_distribution<float> distInitialVelocity(-0.02f, 0.02f);
    std::uniform_real_distribution<float> distVyInitial(-0.05f, -0.01f);
    std::uniform_real_distribution<float> distRotSpeed(-100.0f, 100.0f);
    std::uniform_real_distribution<float> distScale(0.3f, 0.6f);
    std::uniform_real_distribution<float> distLifeTime(5.0f, 15.0f);

    float angle = distAngle(rng);
    float radius = distRadius(rng);
    
    Leaf newLeaf;
    newLeaf.x = treeX + cos(angle) * radius;
    newLeaf.y = treeCenterY + treeLeafSpawnHeightOffset + distHeightOffset(rng);
    newLeaf.z = treeZ + sin(angle) * radius;
    newLeaf.vx = distInitialVelocity(rng);
    newLeaf.vy = distVyInitial(rng);
    newLeaf.vz = distInitialVelocity(rng);
    newLeaf.rotationAngleX = distAngle(rng) * 180.0f / M_PI;
    newLeaf.rotationAngleY = distAngle(rng) * 180.0f / M_PI;
    newLeaf.rotationAngleZ = distAngle(rng) * 180.0f / M_PI;
    newLeaf.rotationSpeedX = distRotSpeed(rng);
    newLeaf.rotationSpeedY = distRotSpeed(rng);
    newLeaf.rotationSpeedZ = distRotSpeed(rng);
    newLeaf.scale = distScale(rng);
    newLeaf.lifeTime = 0.0f;
    newLeaf.maxLifeTime = distLifeTime(rng);
    newLeaf.textureID = leafTextureID;
    
    std::uniform_real_distribution<float> distColor(0.0f, 1.0f);
    float r = 0.1f + distColor(rng) * 0.2f;
    float g = 0.5f + distColor(rng) * 0.3f;
    float b = 0.0f + distColor(rng) * 0.1f;
    newLeaf.color[0] = r;
    newLeaf.color[1] = g;
    newLeaf.color[2] = b;
    newLeaf.color[3] = 0.8f;

    fallingLeaves.push_back(newLeaf);
}

/**
 * @brief 落下する葉パーティクルの位置、回転、速度を更新する。
 * @param deltaTime 前フレームからの経過時間
 */
void updateFallingLeaves(float deltaTime) {
    for (auto& leaf : fallingLeaves) {
        leaf.x += leaf.vx * deltaTime;
        leaf.y += leaf.vy * deltaTime;
        leaf.z += leaf.vz * deltaTime;

        leaf.rotationAngleX += leaf.rotationSpeedX * deltaTime;
        leaf.rotationAngleY += leaf.rotationSpeedY * deltaTime;
        leaf.rotationAngleZ += leaf.rotationSpeedZ * deltaTime;

        leaf.rotationAngleX = fmod(leaf.rotationAngleX, 360.0f);
        leaf.rotationAngleY = fmod(leaf.rotationAngleY, 360.0f);
        leaf.rotationAngleZ = fmod(leaf.rotationAngleZ, 360.0f);

        leaf.lifeTime += deltaTime;
        leaf.vy -= 0.5f * deltaTime;

        float noiseScale = 0.5f;
        float windX = perlinNoise(leaf.x * noiseScale + g_time * 0.1f, leaf.y * noiseScale, leaf.z * noiseScale) * 2.0f - 1.0f;
        float windZ = perlinNoise(leaf.x * noiseScale, leaf.y * noiseScale + g_time * 0.1f, leaf.z * noiseScale) * 2.0f - 1.0f;
        leaf.vx += windX * 0.01f * deltaTime;
        leaf.vz += windZ * 0.01f * deltaTime;
        
        float maxFallSpeed = -0.5f;
        if (leaf.vy < maxFallSpeed) leaf.vy = maxFallSpeed;
    }

    fallingLeaves.erase(std::remove_if(fallingLeaves.begin(), fallingLeaves.end(), 
        [&](const Leaf& leaf) {
            return leaf.y < 0.0f || leaf.lifeTime > leaf.maxLifeTime;
        }), 
        fallingLeaves.end());

    float distToTree = sqrt(pow(cameraX - treeX, 2) + pow(cameraZ - treeZ, 2));
    if (distToTree < 10.0f) {
        std::uniform_int_distribution<int> distChance(0, 99);
        if (distChance(rng) < 10) {
            spawnLeaf(treeY);
        }
    }
}

/**
 * @brief プレイヤーとAABB（軸並行境界ボックス）の当たり判定をチェックし、押し出しベクトルを計算する。
 * @param newX プレイヤーの次のX座標
 * @param newZ プレイヤーの次のZ座標
 * @param correctionX 衝突解決のためのX方向の押し出しベクトル（出力）
 * @param correctionZ 衝突解決のためのZ方向の押し出しベクトル（出力）
 * @return 衝突が発生したかどうか (true/false)
 */
bool checkAABBCollision(float newX, float newZ, float& correctionX, float& correctionZ) {
    correctionX = 0.0f;
    correctionZ = 0.0f;

    for (const auto& box : wallColliders) {
        float closestX = std::max(box.minX, std::min(newX, box.maxX));
        float closestZ = std::max(box.minZ, std::min(newZ, box.maxZ));

        float dx = newX - closestX;
        float dz = newZ - closestZ;
        float distSq = (dx * dx) + (dz * dz);

        if (distSq < (playerRadius * playerRadius)) {
            float dist = sqrt(distSq);
            float overlap = playerRadius - dist;
            if (dist > 0) {
                correctionX = (dx / dist) * overlap;
                correctionZ = (dz / dist) * overlap;
            } else {
                float overlapX1 = newX - box.minX;
                float overlapX2 = box.maxX - newX;
                float overlapZ1 = newZ - box.minZ;
                float overlapZ2 = box.maxZ - newZ;

                float minOverlapX = std::min(overlapX1, overlapX2);
                float minOverlapZ = std::min(overlapZ1, overlapZ2);

                if (minOverlapX < minOverlapZ) {
                    correctionX = (overlapX1 < overlapX2) ? -minOverlapX : minOverlapX;
                } else {
                    correctionZ = (overlapZ1 < overlapZ2) ? -minOverlapZ : minOverlapZ;
                }
            }
            return true;
        }
    }
    return false;
}

/**
 * @brief プレイヤーとOBB（有向境界ボックス）の当たり判定をチェックし、押し出しベクトルを計算する。
 * @param newX プレイヤーの次のX座標
 * @param newZ プレイヤーの次のZ座標
 * @param correctionX 衝突解決のためのX方向の押し出しベクトル（出力）
 * @param correctionZ 衝突解決のためのZ方向の押し出しベクトル（出力）
 * @return 衝突が発生したかどうか (true/false)
 */
bool checkOBBCollision(float newX, float newZ, float& correctionX, float& correctionZ) {
    correctionX = 0.0f;
    correctionZ = 0.0f;

    for (const auto& obb : obbColliders) {
        float cosA_neg = cosf(-obb.angle);
        float sinA_neg = sinf(-obb.angle);
        float dx = newX - obb.cx;
        float dz = newZ - obb.cz;
        float localPlayerX = dx * cosA_neg - dz * sinA_neg;
        float localPlayerZ = dx * sinA_neg + dz * cosA_neg;

        float closestX = std::max(-obb.halfWidth, std::min(localPlayerX, obb.halfWidth));
        float closestZ = std::max(-obb.halfDepth, std::min(localPlayerZ, obb.halfDepth));
        
        Vec2 localPlayerPos = {localPlayerX, localPlayerZ};
        Vec2 closestPoint = {closestX, closestZ};
        Vec2 delta = localPlayerPos - closestPoint;

        if (lengthSq(delta) < (playerRadius * playerRadius)) {
            float dist = length(delta);
            float overlap = playerRadius - dist;
            
            Vec2 localCorrection = {0, 0};
            if (dist > 0) {
                localCorrection = delta * (overlap / dist);
            } else {
                float dx_edge = obb.halfWidth - std::abs(localPlayerX);
                float dz_edge = obb.halfDepth - std::abs(localPlayerZ);
                if (dx_edge < dz_edge) {
                    localCorrection.x = (localPlayerX > 0) ? dx_edge : -dx_edge;
                } else {
                    localCorrection.z = (localPlayerZ > 0) ? dz_edge : -dz_edge;
                }
            }

            float cosA = cosf(obb.angle);
            float sinA = sinf(obb.angle);
            correctionX = localCorrection.x * cosA - localCorrection.z * sinA;
            correctionZ = localCorrection.x * sinA + localCorrection.z * cosA;
            return true;
        }
    }
    return false;
}

/**
 * @brief ゲームの状態を更新するメインループ。glutTimerFuncによって定期的に呼び出される。
 * @param value glutTimerFuncから渡される整数値（ここでは未使用）
 */
void update(int value) {
    float deltaTime = 1.0f / 60.0f;
    g_time += deltaTime;
    updatePallets();
    updateFallingLeaves(deltaTime);

    float forwardX = cos(yaw), forwardZ = sin(yaw), rightX = -forwardZ, rightZ = forwardX;
    float moveX = 0.0f, moveZ = 0.0f;
    if (keyStates['w']) { moveX += forwardX; moveZ += forwardZ; } if (keyStates['s']) { moveX -= forwardX; moveZ -= forwardZ; }
    if (keyStates['a']) { moveX -= rightX; moveZ -= rightZ; } if (keyStates['d']) { moveX += rightX; moveZ += rightZ; }
    
    float magnitude = sqrt(moveX * moveX + moveZ * moveZ);
    if (magnitude > 0) {
        moveX /= magnitude;
        moveZ /= magnitude;
    }
    
    float targetX = cameraX + moveX * moveSpeed;
    float targetZ = cameraZ + moveZ * moveSpeed;

    const int collisionIterations = 3; 
    for (int i = 0; i < collisionIterations; ++i) {
        float correctionX, correctionZ;
        if (checkAABBCollision(targetX, targetZ, correctionX, correctionZ)) {
            targetX += correctionX;
            targetZ += correctionZ;
        }
        if (checkOBBCollision(targetX, targetZ, correctionX, correctionZ)) {
            targetX += correctionX;
            targetZ += correctionZ;
        }
    }

    cameraX = targetX;
    cameraZ = targetZ;
    cameraY = spawnY;
    
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

/**
 * @brief キーボードが押されたときの処理を行う。glutKeyboardFuncに登録される。
 * @param key 押されたキーのASCIIコード
 * @param x マウスカーソルのX座標
 * @param y マウスカーソルのY座標
 */
void keyboard(unsigned char key, int x, int y) {
    keyStates[tolower(key)] = true;
    switch (key) {
        case 27: exit(0); break;
        case 'c':
        case 'C':
            showColliders = !showColliders;
            break;
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
 * @brief キーボードが離されたときの処理を行う。glutKeyboardUpFuncに登録される。
 * @param key 離されたキーのASCIIコード
 * @param x マウスカーソルのX座標
 * @param y マウスカーソルのY座標
 */
void keyboardUp(unsigned char key, int x, int y) { keyStates[tolower(key)] = false; }

/**
 * @brief マウスが動いたときの処理を行い、カメラの向きを更新する。glutPassiveMotionFuncに登録される。
 * @param x マウスカーソルのX座標
 * @param y マウスカーソルのY座標
 */
void mouseMotion(int x, int y) {
    if (!isMouseLookActive) return;

    const int centerX = windowWidth / 2;
    const int centerY = windowHeight / 2;

    if (justWarped) {
        justWarped = false;
        lastMouseX = centerX;
        lastMouseY = centerY;
        return;
    }

    static int reentryFrames = 0;
    const int REENTRY_DURATION = 12;

    if (firstMouse) {
        firstMouse = false;
        lastMouseX = x;
        lastMouseY = y;
        reentryFrames = REENTRY_DURATION;
        return;
    }

    float deltaX = static_cast<float>(x - lastMouseX);
    float deltaY = static_cast<float>(lastMouseY - y);

    const float maxDelta = 200.0f;
    if (deltaX > maxDelta) deltaX = maxDelta;
    if (deltaX < -maxDelta) deltaX = -maxDelta;
    if (deltaY > maxDelta) deltaY = maxDelta;
    if (deltaY < -maxDelta) deltaY = -maxDelta;

    float fadeFactor = 1.0f;
    if (reentryFrames > 0) {
        fadeFactor = (float)(REENTRY_DURATION - reentryFrames + 1) / (float)REENTRY_DURATION;
        reentryFrames--;
    }

    yaw   += deltaX * mouseSensitivity * fadeFactor;
    pitch += deltaY * mouseSensitivity * fadeFactor;

    const float pitchLimit = M_PI_2 - 0.1f;
    if (pitch > pitchLimit) pitch = pitchLimit;
    if (pitch < -pitchLimit) pitch = -pitchLimit;

    if (yaw > M_PI) yaw -= 2.0f * M_PI;
    if (yaw <= -M_PI) yaw += 2.0f * M_PI;

    lastMouseX = x;
    lastMouseY = y;

    const int edgeThreshold = 20;
    if (x < edgeThreshold || x > windowWidth - edgeThreshold ||
        y < edgeThreshold || y > windowHeight - edgeThreshold) {
        glutWarpPointer(centerX, centerY);
        justWarped = true;
        lastMouseX = centerX;
        lastMouseY = centerY;
    }
}

/**
 * @brief ウィンドウサイズが変更されたときの処理を行う。glutReshapeFuncに登録される。
 * @param w 新しいウィンドウの幅
 * @param h 新しいウィンドウの高さ
 */
void reshape(int w, int h) {
    windowWidth = w; 
    windowHeight = h > 0 ? h : 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
    
    float aspect = (double)w / (double)h;
    float perspectiveMat[16];
    perspectiveMatrix(perspectiveMat, 45.0, aspect, 0.1, 200.0);
    glLoadMatrixf(perspectiveMat);

    glMatrixMode(GL_MODELVIEW);
}

/**
 * @brief マウスカーソルがウィンドウ内に入った/出たときの処理を行う。glutEntryFuncに登録される。
 * @param state マウスカーソルの状態 (GLUT_ENTERED or GLUT_LEFT)
 */
void entry(int state) {
    if (state == GLUT_ENTERED) {
        isMouseLookActive = true;
        firstMouse = true;
    } else if (state == GLUT_LEFT) {
        isMouseLookActive = false;
    }
}

/**
 * @brief シーンの初期化を行う。背景色、照明、テクスチャ、モデルの読み込みなどを実行する。
 */
void initScene() {
    glClearColor(0.05f, 0.05f, 0.15f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat global_ambient[] = { 0.1f, 0.1f, 0.15f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    GLfloat light_pos[] = { 5.0f, 10.0f, 5.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    GLfloat light_diffuse[] = {0.5f, 0.5f, 0.7f, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    GLfloat light_specular[] = {0.7f, 0.7f, 0.8f, 1.0f};
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glEnable(GL_FOG);
    GLfloat fogColor[] = {0.05f, 0.05f, 0.15f, 1.0f};
    glFogi(GL_FOG_MODE, GL_EXP2);
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_DENSITY, 0.015f);
    
    if (!loadTexture("ground.jpg", groundTextureID)) { 
        printf("Failed to load ground texture.\n"); 
    }
    if (!loadTexture("wall.jpg", wallTextureID)) {
        printf("Failed to load wall texture.\n");
    }
    if (!loadTexture("stone.jpg", rockTextureID)) {
        printf("Failed to load rock texture.\n");
    }
    if (!loadTexture("leaf.jpg", leafTextureID, false)) { 
        printf("Failed to load leaf texture.\n");
    }

    glEnable(GL_TEXTURE_2D);
    if(!loadObjModel(paletModel, "../obj/palet.obj")) { std::cerr << "Failed to load palet.obj" << std::endl; }
    if(!loadObjModel(blenderModel, "../obj/house.obj")) { std::cerr << "Failed to load house.obj" << std::endl; }
    setupColliders();
    setupPallets();
    initPerlinNoise();
}

/**
 * @brief メイン関数。プログラムのエントリーポイント。
 * @param argc コマンドライン引数の数
 * @param argv コマンドライン引数の配列
 * @return 終了コード
 */
int main(int argc, char** argv) {
    setlocale(LC_NUMERIC, "C");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("3D FPS Controller - GLU Free Version (Night)");
    glutFullScreen();
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
