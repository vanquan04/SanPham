#include "glut.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void drawTham() {
    glPushMatrix();


    glTranslatef(0.0f, 0.01f, 0.0f);

    // Vẽ thảm chính màu đỏ
    glColor3f(0.8f, 0.2f, 0.2f); // Màu đỏ đậm
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(-2.0f, 0, -1.5f);
    glVertex3f(-2.0f, 0, 1.5f);
    glVertex3f(2.0f, 0, 1.5f);
    glVertex3f(2.0f, 0, -1.5f);
    glEnd();

    // Vẽ viền thảm màu vàng gold
    glColor3f(0.9f, 0.7f, 0.2f); // Màu vàng gold
    float vienRong = 0.1f;

    // Viền trên
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(-2.0f, 0.001f, 1.5f);
    glVertex3f(-2.0f, 0.001f, 1.5f - vienRong);
    glVertex3f(2.0f, 0.001f, 1.5f - vienRong);
    glVertex3f(2.0f, 0.001f, 1.5f);
    glEnd();

    // Viền dưới
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(-2.0f, 0.001f, -1.5f + vienRong);
    glVertex3f(-2.0f, 0.001f, -1.5f);
    glVertex3f(2.0f, 0.001f, -1.5f);
    glVertex3f(2.0f, 0.001f, -1.5f + vienRong);
    glEnd();

    // Viền trái
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(-2.0f, 0.001f, -1.5f);
    glVertex3f(-2.0f, 0.001f, 1.5f);
    glVertex3f(-2.0f + vienRong, 0.001f, 1.5f);
    glVertex3f(-2.0f + vienRong, 0.001f, -1.5f);
    glEnd();

    // Viền phải
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(2.0f - vienRong, 0.001f, -1.5f);
    glVertex3f(2.0f - vienRong, 0.001f, 1.5f);
    glVertex3f(2.0f, 0.001f, 1.5f);
    glVertex3f(2.0f, 0.001f, -1.5f);
    glEnd();

    // Vẽ hoa văn trang trí ở giữa thảm
    glColor3f(0.9f, 0.5f, 0.5f); // Màu hồng nhạt

    // Hoa văn hình thoi ở giữa
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(-0.8f, 0.002f, 0.0f);
    glVertex3f(0.0f, 0.002f, 0.6f);
    glVertex3f(0.8f, 0.002f, 0.0f);
    glVertex3f(0.0f, 0.002f, -0.6f);
    glEnd();

    // Các hoa văn nhỏ ở 4 góc
    glColor3f(0.9f, 0.7f, 0.3f); // Màu vàng nhạt

    // Góc trái trên
    glPushMatrix();
    glTranslatef(-1.3f, 0.002f, 0.8f);
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 1, 0);
    glVertex3f(0.0f, 0.0f, 0.0f); // Tâm
    for (int i = 0; i <= 8; i++) {
        float angle = i * M_PI / 4.0f;
        float x = 0.2f * cos(angle);
        float z = 0.2f * sin(angle);
        glVertex3f(x, 0.0f, z);
    }
    glEnd();
    glPopMatrix();

    // Góc phải trên
    glPushMatrix();
    glTranslatef(1.3f, 0.002f, 0.8f);
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 1, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    for (int i = 0; i <= 8; i++) {
        float angle = i * M_PI / 4.0f;
        float x = 0.2f * cos(angle);
        float z = 0.2f * sin(angle);
        glVertex3f(x, 0.0f, z);
    }
    glEnd();
    glPopMatrix();

    // Góc trái dưới
    glPushMatrix();
    glTranslatef(-1.3f, 0.002f, -0.8f);
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 1, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    for (int i = 0; i <= 8; i++) {
        float angle = i * M_PI / 4.0f;
        float x = 0.2f * cos(angle);
        float z = 0.2f * sin(angle);
        glVertex3f(x, 0.0f, z);
    }
    glEnd();
    glPopMatrix();

    // Góc phải dưới
    glPushMatrix();
    glTranslatef(1.3f, 0.002f, -0.8f);
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 1, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    for (int i = 0; i <= 8; i++) {
        float angle = i * M_PI / 4.0f;
        float x = 0.2f * cos(angle);
        float z = 0.2f * sin(angle);
        glVertex3f(x, 0.0f, z);
    }
    glEnd();
    glPopMatrix();

    glPopMatrix();
}