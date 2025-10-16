#include <GL/glew.h>
#define FREEGLUT_STATIC
#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <iostream>
#include <string>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

// グローバル変数
tinyobj::attrib_t attrib;
std::vector<tinyobj::shape_t> shapes;
std::vector<tinyobj::material_t> materials;
float rotationAngle = 0.0f;

// モデル読み込み関数
bool loadObjModel(const std::string& filepath) {
    std::string warn, err;
    std::string base_dir = filepath.substr(0, filepath.find_last_of("/\\") + 1);
    bool success = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filepath.c_str(), base_dir.c_str());
    if (!warn.empty()) { std::cout << "WARN: " << warn << std::endl; }
    if (!err.empty()) { std::cerr << "ERR: " << err << std::endl; }
    if(success) { std::cout << "Successfully loaded model: " << filepath << std::endl; }
    return success;
}

// モデル描画関数
void drawObjModel() {
    if (shapes.empty()) return;
    for (const auto& shape : shapes) {
        size_t index_offset = 0;
        for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++) {
            int fv = shape.mesh.num_face_vertices[f];
            int material_id = shape.mesh.material_ids[f];

            if (material_id < 0 || material_id >= materials.size()) {
                GLfloat default_mat[] = {0.8f, 0.8f, 0.8f, 1.0f};
                glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, default_mat);
            } else {
                const auto& mat = materials[material_id];
                glMaterialfv(GL_FRONT, GL_AMBIENT, mat.ambient);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, mat.diffuse);
                glMaterialfv(GL_FRONT, GL_SPECULAR, mat.specular);
                glMaterialf(GL_FRONT, GL_SHININESS, mat.shininess);
            }

            glBegin(GL_TRIANGLES);
            for (size_t v = 0; v < fv; v++) {
                tinyobj::index_t idx = shape.mesh.indices[index_offset + v];
                if (idx.normal_index >= 0) {
                    glNormal3fv(&attrib.normals[3 * idx.normal_index]);
                }
                glVertex3fv(&attrib.vertices[3 * idx.vertex_index]);
            }
            glEnd();
            index_offset += fv;
        }
    }
}

// 描画コールバック関数
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 3.0, 5.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0);

    glPushMatrix();
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
    glScalef(0.01f, 0.01f, 0.01f); // モデルのサイズ調整（適宜変更してください）
    drawObjModel();
    glPopMatrix();
    
    glutSwapBuffers();
}

// アニメーション用タイマー関数
void timer(int value) {
    rotationAngle += 0.5f;
    if (rotationAngle > 360.0f) {
        rotationAngle -= 360.0f;
    }
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

// ウィンドウリサイズ用コールバック関数
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// ★修正: 初期化関数
void init() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // ★追加: シーン全体を照らす「グローバル環境光」
    GLfloat global_ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    // こちらは個別の光源（太陽や電球のようなもの）の設定
    GLfloat light_pos[] = { 5.0f, 10.0f, 5.0f, 1.0f }; // 位置
    GLfloat light_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // 拡散光（色）
    GLfloat light_spc[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // 鏡面光（ハイライト）
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_dif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_spc);
    
    // モデルの読み込み (パスはご自身の環境に合わせてください)
    if(!loadObjModel("../obj/test.obj")) {
        std::cerr << "Failed to load model" << std::endl;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Simple OBJ Loader Test");

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return 1;
    }

    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    
    glutMainLoop();
    return 0;
}
