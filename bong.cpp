#include "bong.h"
#include "glut.h"
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Biến lưu trữ vị trí hiện tại của quả bóng
static float ballPosX = 0.0f;
static float ballPosY = 0.5f;  // Đặt trên sàn nhà
static float ballPosZ = 0.0f;

// Hàm thiết lập vị trí cho quả bóng
void setBallPosition(float x, float y, float z) {
    ballPosX = x;
    ballPosY = y;
    ballPosZ = z;
}
// Hàm vẽ quả bóng tại vị trí đã được thiết lập
void drawBall() {
    glPushMatrix();
    glTranslatef(ballPosX, ballPosY, ballPosZ);

    // Vẽ quả bóng màu cam
    glColor3f(1.0f, 0.55f, 0.0f);  // Màu cam đặc trưng của bóng rổ
    glutSolidSphere(0.5, 64, 64);

    // Vẽ các đường sọc đen mô phỏng đường trên quả bóng rổ
    glColor3f(0.0f, 0.0f, 0.0f);

    // Đường ngang quanh "xích đạo"
    glPushMatrix();
    glRotatef(90, 1, 0, 0);  // Xoay quanh trục X
    glutSolidTorus(0.005, 0.5, 16, 64);
    glPopMatrix();

    // Đường dọc quanh trục Z
    glPushMatrix();
    glRotatef(0, 0, 1, 0);  // Không xoay
    glutSolidTorus(0.005, 0.5, 16, 64);
    glPopMatrix();

    // Đường dọc quanh trục X
    glPushMatrix();
    glRotatef(90, 0, 1, 0);  // Xoay quanh trục Y
    glutSolidTorus(0.005, 0.5, 16, 64);
    glPopMatrix();

    // Đường cong chéo
    glPushMatrix();
    glRotatef(45, 1, 0, 0);
    glutSolidTorus(0.005, 0.5, 16, 64);
    glPopMatrix();

    glPopMatrix();
}