#include "glut.h"
#include "xe.h"
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Vị trí và góc quay của máy xúc
float xePosX = 0.0f;
float xePosZ = 0.0f;
float gocQuay = 0.0f;


void drawBanhXe(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(0.2f, 0.2f, 0.2f);
    glScalef(0.1f, 0.1f, 0.05f);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawCabin() {
    // Cabin lái xe
    glPushMatrix();
    glColor3f(0.3f, 0.5f, 0.8f);
    glTranslatef(0.0f, 0.3f, 0.0f);
    glScalef(0.25f, 0.2f, 0.25f);
    glutSolidCube(1.0);
    glPopMatrix();

    // Kính cabin trước
    glPushMatrix();
    glColor3f(0.7f, 0.9f, 1.0f);
    glTranslatef(0.125f, 0.3f, 0.0f);
    glScalef(0.02f, 0.15f, 0.2f);
    glutSolidCube(1.0);
    glPopMatrix();

    // Kính cabin sau
    glPushMatrix();
    glColor3f(0.7f, 0.9f, 1.0f);
    glTranslatef(-0.125f, 0.3f, 0.0f);
    glScalef(0.02f, 0.15f, 0.2f);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawGauXuc() {
    // Gầu xúc chính
    glPushMatrix();
    glColor3f(0.6f, 0.4f, 0.1f);
    glScalef(0.2f, 0.12f, 0.18f);
    glutSolidCube(1.0);
    glPopMatrix();

    // Răng gầu xúc
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glColor3f(0.7f, 0.5f, 0.2f);
        glTranslatef(-0.08f + i * 0.053f, -0.1f, 0.09f);
        glScalef(0.02f, 0.04f, 0.02f);
        glutSolidCube(1.0);
        glPopMatrix();
    }
}

void drawCanXuc() {
    // Cần xúc chính (từ cabin ra phía trước)
    glPushMatrix();
    glColor3f(0.9f, 0.7f, 0.1f);
    glTranslatef(0.2f, 0.0f, 0.0f);
    glScalef(0.3f, 0.06f, 0.06f);
    glutSolidCube(1.0);
    glPopMatrix();

    // Cần xúc phụ (từ cần chính xuống gầu)
    glPushMatrix();
    glTranslatef(0.35f, 0.0f, 0.0f);
    glColor3f(0.8f, 0.6f, 0.0f);
    glTranslatef(0.08f, -0.08f, 0.0f);
    glScalef(0.16f, 0.05f, 0.05f);
    glutSolidCube(1.0);
    glPopMatrix();

    // Gầu xúc
    glPushMatrix();
    glTranslatef(0.5f, -0.15f, 0.0f);
    drawGauXuc();
    glPopMatrix();
}

void drawXeMayXuc() {
    glPushMatrix();

    // Đặt vị trí và góc quay
    glTranslatef(xePosX, 0.0f, xePosZ);
    glRotatef(gocQuay, 0.0f, 1.0f, 0.0f);

    // Thân xe chính
    glPushMatrix();
    glColor3f(0.8f, 0.2f, 0.2f);
    glTranslatef(0.0f, 0.12f, 0.0f);
    glScalef(0.7f, 0.15f, 0.35f);
    glutSolidCube(1.0);
    glPopMatrix();

    // Bánh xe
    drawBanhXe(-0.28f, 0.05f, -0.15f);
    drawBanhXe(-0.28f, 0.05f, 0.15f);
    drawBanhXe(0.28f, 0.05f, -0.15f);
    drawBanhXe(0.28f, 0.05f, 0.15f);

    // Cabin
    drawCabin();

    // Khối động cơ
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f);
    glTranslatef(-0.25f, 0.2f, 0.0f);
    glScalef(0.2f, 0.12f, 0.25f);
    glutSolidCube(1.0);
    glPopMatrix();

    // Hệ thống cần xúc
    glPushMatrix();
    glTranslatef(0.0f, 0.25f, 0.0f);
    drawCanXuc();
    glPopMatrix();

    // Đèn trước
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.8f);
    glTranslatef(0.35f, 0.2f, -0.1f);
    glutSolidSphere(0.03f, 8, 8);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.8f);
    glTranslatef(0.35f, 0.2f, 0.1f);
    glutSolidSphere(0.03f, 8, 8);
    glPopMatrix();

    // Ống xả
    glPushMatrix();
    glColor3f(0.4f, 0.4f, 0.4f);
    glTranslatef(-0.3f, 0.35f, 0.08f);
    glScalef(0.03f, 0.15f, 0.03f);
    glutSolidCube(1.0);
    glPopMatrix();

    // Bình nhiên liệu
    glPushMatrix();
    glColor3f(0.2f, 0.6f, 0.2f);
    glTranslatef(-0.15f, 0.35f, -0.1f);
    glScalef(0.08f, 0.1f, 0.08f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();
}

void updateXeCanCauTransform(unsigned char key) {
    float moveSpeed = 0.05f;
    float rotateSpeed = 3.0f;

    switch (key) {
    case '1': // Xoay trái
        gocQuay += rotateSpeed;
        break;
    case '2': // Xoay phải
        gocQuay -= rotateSpeed;
        break;
    case '3': // Di chuyển tiến
        xePosX += moveSpeed * sin(gocQuay * M_PI / 180.0f);
        xePosZ += moveSpeed * cos(gocQuay * M_PI / 180.0f);
        break;
    case '4': // Di chuyển lùi
        xePosX -= moveSpeed * sin(gocQuay * M_PI / 180.0f);
        xePosZ -= moveSpeed * cos(gocQuay * M_PI / 180.0f);
        break;
    }
}