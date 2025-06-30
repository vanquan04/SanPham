#include "cua.h"

// Hàm v? m?t càng cua
void drawClaw(bool isLeft) {
    float dir = isLeft ? -1.0f : 1.0f;

    // Cánh tay n?i t? thân chân càng
    glPushMatrix();
    glTranslatef(dir * 0.35f, 0.05f, 0.2f);
    glRotatef(dir * 30, 0, 0, 1);
    glScalef(0.25f, 0.08f, 0.08f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Ph?n càng chính (hình kh?i l?n)
    glPushMatrix();
    glTranslatef(dir * 0.55f, 0.1f, 0.2f);
    glRotatef(dir * 20, 0, 0, 1);
    glScalef(0.25f, 0.08f, 0.08f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // M?i k?p trên
    glPushMatrix();
    glTranslatef(dir * 0.65f, 0.16f, 0.2f);
    glRotatef(dir * 25, 0, 0, 1);
    glScalef(0.15f, 0.05f, 0.05f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // M?i k?p d??i
    glPushMatrix();
    glTranslatef(dir * 0.65f, 0.04f, 0.2f);
    glRotatef(dir * -25, 0, 0, 1);
    glScalef(0.15f, 0.05f, 0.05f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

// Hàm v? con cua
void drawToyCrab(float x, float y, float z, float scale) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(scale, scale, scale);

    // Thân cua
    glColor3f(1.0f, 0.4f, 0.2f);
    glPushMatrix();
    glScalef(1.2f, 0.6f, 0.8f);
    glutSolidSphere(0.3f, 20, 16);
    glPopMatrix();

    // Càng cua
    glColor3f(1.0f, 0.3f, 0.1f);
    drawClaw(true);  // bên trái
    drawClaw(false); // bên ph?i

    // Chân cua - 6 chân m?i bên
    glColor3f(0.8f, 0.3f, 0.1f);
    for (int i = 0; i < 3; i++) {
        float legZ = -0.2f + i * 0.2f;

        // Chân trái
        glPushMatrix();
        glTranslatef(-0.35f, -0.25f, legZ);
        glRotatef(30, 0, 0, 1);
        glScalef(0.3f, 0.05f, 0.05f);
        glutSolidCube(1.0f);
        glPopMatrix();

        // Chân ph?i
        glPushMatrix();
        glTranslatef(0.35f, -0.25f, legZ);
        glRotatef(-30, 0, 0, 1);
        glScalef(0.3f, 0.05f, 0.05f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }

    // M?t cua
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(-0.15f, 0.2f, 0.25f);
    glutSolidSphere(0.05f, 8, 6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.15f, 0.2f, 0.25f);
    glutSolidSphere(0.05f, 8, 6);
    glPopMatrix();

    glPopMatrix();
}
