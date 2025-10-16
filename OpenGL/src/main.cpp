#include <GL/glut.h>

#define _USE_MATH_DEFINES  // Ensure M_PI is defined
#include <math.h>



#define PART 100 // 分割数


/* 円を描く関数 */
void draw_circle(float r, float r2, float X, float Y)
{
  int i, n = 100;
  float x, y;
  double rate;

  glBegin(GL_POLYGON);
  for (i = 0; i < n; i++) {
    rate = (double)i / n;  //座標を計算
    x = r * cos(2.0 * M_PI * rate) + X;
    y = r2 * sin(2.0 * M_PI * rate) + Y;
    glVertex3f(x, y, 0.0); // 頂点座標を指定
  }
  glEnd();
}

/* お腹の模様 */
void draw_moyou(float x, float y)
{
  glBegin(GL_POLYGON);
  glVertex2d(0 + x, -0.04 + y);
  glVertex2d(0.05 + x, -0.1 + y);
  glVertex2d(0.0 + x, -0.08 + y);
  glVertex2d(-0.05+ x, -0.1 + y);
  glEnd();
}

/* お腹 */
void draw_onaka(void)
{
  draw_moyou(0,0.23);
  draw_moyou(0.2,0.19); 
  draw_moyou(-0.2,0.19);
  draw_moyou(0.1,0.1);
  draw_moyou(-0.1,0.1);
  draw_moyou(0.3,0.05);
  draw_moyou(-0.3,0.05);

  glBegin(GL_TRIANGLES);
  glColor3d(1.0, 1.0, 0.9);
  glVertex2d(0.49, -0.4);
  glVertex2d(-0.49, -0.4);
  glColor3d(1.0, 1.0, 1.0);
  glVertex2d(0.0, -0.85);
  glEnd();
  
}

/* 目 */
void draw_eyes(void)
{  
  glColor3d(1.0, 1.0, 1.0);
  draw_circle(0.05, 0.05, 0.25, 0.42);
  draw_circle(0.05, 0.05, -0.25, 0.42);

  glColor3d(0.0, 0.0, 0.0);
  draw_circle(0.02, 0.02, 0.25, 0.42);
  draw_circle(0.02, 0.02, -0.25, 0.42);
}

/* 鼻 */
void draw_nose(void)
{
  glColor3d(0.0, 0.0, 0.0);
  glBegin(GL_TRIANGLES);
  glVertex2d(0, 0.4);
  glVertex2d(0.05, 0.44);
  glVertex2d(-0.05, 0.44);
  glEnd();
}

/* 耳 */
void draw_ears(void)
{
  glColor3d(0.75, 0.75, 0.75); /* 体の色 */
  glBegin(GL_TRIANGLES);
  glVertex2d(-0.4, 0.9);
  glVertex2d(-0.43, 0.55);
  glVertex2d(-0.3, 0.65);
  glEnd();

  glBegin(GL_TRIANGLES);
  glVertex2d(0.4, 0.9);
  glVertex2d(0.43, 0.55);
  glVertex2d(0.3, 0.65);
  glEnd();

  glBegin(GL_QUADS);
  glVertex2d(-0.4, 0.6);
  glVertex2d(-0.35, 0.5);
  glVertex2d(-0.29, 0.55);
  glVertex2d(-0.34, 0.65);
  glEnd();

  glBegin(GL_QUADS);
  glVertex2d(0.4, 0.6);
  glVertex2d(0.35, 0.5);
  glVertex2d(0.29, 0.55);
  glVertex2d(0.34, 0.65);
  glEnd();
}  

/* 足 */
void draw_feet(void)
{  
  glColor3d(0.0, 0.0, 0.0); /* 爪 */
  glBegin(GL_TRIANGLES);
  glVertex2d(-0.5, -0.85);  /* 左 */
  glVertex2d(-0.6, -0.85);
  glVertex2d(-0.5, -0.82);

  glVertex2d(0.5, -0.85);  /* 右 */
  glVertex2d(0.6, -0.85);
  glVertex2d(0.5, -0.82);
  glEnd();

  glColor3d(0.75, 0.75, 0.75); /* 体の色 足*/
  glBegin(GL_TRIANGLES);
  glVertex2d(0, -0.85);  /* 左 */
  glVertex2d(-0.5, -0.85);
  glVertex2d(-0.63, -0.3);

  glVertex2d(0, -0.85);  /* 右 */
  glVertex2d(0.5, -0.85);
  glVertex2d(0.63, -0.3);
  glEnd();  

}

/* ひげ */
void draw_hige(void)
{
  glColor3d(0.0, 0.0, 0.0);  /* 黒 */
  glBegin(GL_LINES);
  glVertex2d(-0.8, 0.4);  /* 左 */
  glVertex2d(-0.4, 0.38);
  glVertex2d(-0.85, 0.35);
  glVertex2d(-0.45, 0.34);
  glVertex2d(-0.8, 0.3);
  glVertex2d(-0.4, 0.3);

  glVertex2d(0.8, 0.4);  /* 右 */
  glVertex2d(0.4, 0.38);
  glVertex2d(0.85, 0.35);
  glVertex2d(0.45, 0.34);
  glVertex2d(0.8, 0.3);
  glVertex2d(0.4, 0.3);
  glEnd();
}

/* 口 */
void draw_mouse(void)
{
  glColor3d(1.0, 1.0, 1.0);  /* 白 */
  glBegin(GL_TRIANGLES);
  glVertex2d(-0.3, 0.34);
  glVertex2d(0.3, 0.34);
  glVertex2d(0, 0.28);
  glEnd();

  glColor3d(0.0, 0.0, 0.0);  /* 黒 */
  glBegin(GL_LINES);  /* 縦ライン */
  glVertex2d(0, 0.34);
  glVertex2d(0, 0.28);
  glVertex2d(-0.1, 0.34);
  glVertex2d(-0.1, 0.3);
  glVertex2d(0.1, 0.34);
  glVertex2d(0.1, 0.3);
  glVertex2d(0.2, 0.34);
  glVertex2d(0.2, 0.32);
  glVertex2d(-0.2, 0.34);
  glVertex2d(-0.2, 0.32);
  glEnd();  
}

/* 顔のパーツを描画 */
void draw_fice(void)
{
  draw_eyes();
  draw_nose();
  draw_ears();
  draw_hige();
  draw_mouse();
}

/* 手 */
void draw_hands(void)
{ 
  glColor3d(0.0, 0.0, 0.0);  /* 黒 */
  glBegin(GL_TRIANGLES);
  glVertex2d(-0.59, -0.6);
  glVertex2d(-0.61, -0.4);
  glVertex2d(-0.57, -0.4);
  glEnd();

  glBegin(GL_TRIANGLES);
  glVertex2d(0.59, -0.6);
  glVertex2d(0.61, -0.4);
  glVertex2d(0.57, -0.4);
  glEnd();

  glColor3d(0.75, 0.75, 0.75);  /* 体の色 */
  draw_circle(0.2, 0.4, -0.5, -0.15);
  draw_circle(0.2, 0.4, 0.5, -0.15);
  //  glColor3d(0.0, 0.0, 0.0);
  glEnd();
}

void display(void)
{  
  glClear(GL_COLOR_BUFFER_BIT);  // ウィンドウを塗りつぶす

  glBegin(GL_QUADS);  // 背景のグラデーション
  glColor3d(0.67, 1.0, 0.18);
  glVertex2d(-1.0, -1.0);
  glVertex2d(1.0, -1.0);
  glColor3d(0.68, 0.93, 0.93);
  glVertex2d(1.0, 1.0); 
  glVertex2d(-1.0, 1.0);
  glEnd();

  draw_feet();
  draw_hands();
  glColor3d(0.75, 0.75, 0.75); // 体の色 
  draw_circle(0.65, 0.75, 0, -0.1);
  glColor3d(1.0, 1.0, 0.9); // お腹の色 
  draw_circle(0.55, 0.55, 0, -0.3);
  glColor3d(0.75, 0.75, 0.75); // 体の色
  draw_onaka();  // お腹の模様を描画 
  draw_fice();  // 顔のパーツを描画 
  glFlush();
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);  // 環境の初期化
  glutInitDisplayMode(GLUT_RGBA);  // 色の指定を決める 
  glutCreateWindow(argv[0]);  // ウィンドウを開く
  glutDisplayFunc(display);  // 絵を描く関数を決める
  glutMainLoop();  // イベントの待ち受け状態
  return 0;
}
